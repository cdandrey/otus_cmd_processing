#include <iostream>
#include <string>

#include "cmd_processing.h"
#include "cmd_handler.h"
#include "cmd_types.h"

bool BulkBeginHandler::done(CmdProcessingPtr /*cmdProcessing*/)
{
    return false;
}

void BulkBeginHandler::read(CmdProcessingPtr cmdProcessing)
{
    auto [result,data] = cmdProcessing->read();

    if (!result) {
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkEndHandler{}));
    } else if (data == commands::CmdOpenBulk) {
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkDynamicHandler{1}));
    } else {
        cmdProcessing->push(data);
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkStaticHandler{cmdProcessing->bulkSize()}));
    }
}

BulkDynamicHandler::BulkDynamicHandler(int countOpenBulk)
    : m_countOpenBulk{countOpenBulk}
{
}

bool BulkDynamicHandler::done(CmdProcessingPtr cmdProcessing)
{
    if (m_countOpenBulk == 0) {
        cmdProcessing->pull();
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkBeginHandler{}));
    }

    return false;
}

void BulkDynamicHandler::read(CmdProcessingPtr cmdProcessing)
{
    auto [result,data] = cmdProcessing->read();

    if (!result) {
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkEndHandler{}));
    } else if (data == commands::CmdOpenBulk){
        ++m_countOpenBulk;
    } else if (data == commands::CmdCloseBulk) {
        --m_countOpenBulk;
    } else {
        cmdProcessing->push(data);
    }
}

BulkStaticHandler::BulkStaticHandler(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

bool BulkStaticHandler::done(CmdProcessingPtr cmdProcessing)
{
    if (m_bulkSize == 0) {
        cmdProcessing->pull();
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkBeginHandler{}));
    }

    return false;
}

void BulkStaticHandler::read(CmdProcessingPtr cmdProcessing)
{
    auto [result,data] = cmdProcessing->read();

    if (!result) {
        cmdProcessing->pull();
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkEndHandler{}));
    } else if (data == commands::CmdOpenBulk) {
        cmdProcessing->pull();
        cmdProcessing->set_state(std::make_unique<ICmdHandler>(new BulkDynamicHandler{1}));
    } else {
        cmdProcessing->push(data);
        --m_bulkSize;
    }
}

bool BulkEndHandler::done(CmdProcessingPtr /*cmdProcessing*/)
{
    return true;
}

void BulkEndHandler::read(CmdProcessingPtr /*cmdProcessing*/) 
{
}