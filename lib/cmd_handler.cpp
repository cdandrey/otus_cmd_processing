#include <iostream>
#include <string>

#include "cmd_processing.h"
#include "cmd_handler.h"

namespace detail 
{
const std::string CmdOpenBulk = "{";
const std::string CmdCloseBulk = "}";
}   // namespace detail

namespace cmd 
{

bool BulkBeginHandler::done(CmdProcessing* /*cmdProcessing*/)
{
    return false;
}

void BulkBeginHandler::read(CmdProcessing* cmdProcessing)
{
    auto [result,data] = cmdProcessing->read();

    if (!result) {
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkEndHandler{}});
    } else if (data == detail::CmdOpenBulk) {
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkDynamicHandler{1}});
    } else {
        cmdProcessing->push(data);
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkStaticHandler{cmdProcessing->bulkSize() - 1}});
    }
}

BulkDynamicHandler::BulkDynamicHandler(int countOpenBulk)
    : m_countOpenBulk{countOpenBulk}
{
}

bool BulkDynamicHandler::done(CmdProcessing* cmdProcessing)
{
    if (m_countOpenBulk == 0) {
        cmdProcessing->output();
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkBeginHandler{}});
    }

    return false;
}

void BulkDynamicHandler::read(CmdProcessing* cmdProcessing)
{
    auto [result,data] = cmdProcessing->read();

    if (!result) {
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkEndHandler{}});
    } else if (data == detail::CmdOpenBulk){
        ++m_countOpenBulk;
    } else if (data == detail::CmdCloseBulk) {
        --m_countOpenBulk;
    } else {
        cmdProcessing->push(data);
    }
}

BulkStaticHandler::BulkStaticHandler(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

bool BulkStaticHandler::done(CmdProcessing* cmdProcessing)
{
    if (m_bulkSize == 0) {
        cmdProcessing->output();
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkBeginHandler{}});
    }

    return false;
}

void BulkStaticHandler::read(CmdProcessing* cmdProcessing)
{
    auto [result,data] = cmdProcessing->read();

    if (!result) {
        cmdProcessing->output();
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkEndHandler{}});
    } else if (data == detail::CmdOpenBulk) {
        cmdProcessing->output();
        cmdProcessing->set_handler(ICmdHandlerPtr{new BulkDynamicHandler{1}});
    } else {
        cmdProcessing->push(data);
        --m_bulkSize;
    }
}

bool BulkEndHandler::done(CmdProcessing* /*cmdProcessing*/)
{
    return true;
}

void BulkEndHandler::read(CmdProcessing* /*cmdProcessing*/) 
{
}

} // namespace cmd