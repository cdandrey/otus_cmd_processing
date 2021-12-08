#include <iostream>
#include <string>

#include "CommandProcessing.h"
#include "AbstractCommandHandler.h"

namespace detail
{
const std::string CmdOpenBulk{ "{" };
const std::string CmdCloseBulk{ "}" };
} // namespace detail

namespace cmd
{

bool BulkBeginHandler::done(CommandProcessing* /*CommandProcessing*/)
{
    return false;
}

void BulkBeginHandler::read(CommandProcessing* CommandProcessing)
{
    auto [result, data] = CommandProcessing->read();

    if (!result)
    {
        CommandProcessing->set_handler(std::make_unique<BulkEndHandler>());
    }
    else if (data == detail::CmdOpenBulk)
    {
        CommandProcessing->set_handler(std::make_unique<BulkDynamicHandler>(1));
    }
    else
    {
        CommandProcessing->push(data);
        CommandProcessing->set_handler(std::make_unique<BulkStaticHandler>(CommandProcessing->bulkSize() - 1));
    }
}

BulkDynamicHandler::BulkDynamicHandler(int countOpenBulk)
    : m_countOpenBulk{ countOpenBulk }
{
}

bool BulkDynamicHandler::done(CommandProcessing* CommandProcessing)
{
    if (m_countOpenBulk == 0)
    {
        CommandProcessing->output();
        CommandProcessing->set_handler(AbstractCommandHandlerPtr{ new BulkBeginHandler{} });
    }

    return false;
}

void BulkDynamicHandler::read(CommandProcessing* CommandProcessing)
{
    auto [result, data] = CommandProcessing->read();

    if (!result)
    {
        CommandProcessing->set_handler(std::make_unique<BulkEndHandler>());
    }
    else if (data == detail::CmdOpenBulk)
    {
        ++m_countOpenBulk;
    }
    else if (data == detail::CmdCloseBulk)
    {
        --m_countOpenBulk;
    }
    else
    {
        CommandProcessing->push(data);
    }
}

BulkStaticHandler::BulkStaticHandler(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

bool BulkStaticHandler::done(CommandProcessing* CommandProcessing)
{
    if (m_bulkSize == 0)
    {
        CommandProcessing->output();
        CommandProcessing->set_handler(std::make_unique<BulkBeginHandler>());
    }

    return false;
}

void BulkStaticHandler::read(CommandProcessing* CommandProcessing)
{
    auto [result, data] = CommandProcessing->read();

    if (!result)
    {
        CommandProcessing->output();
        CommandProcessing->set_handler(std::make_unique<BulkBeginHandler>());
    }
    else if (data == detail::CmdOpenBulk)
    {
        CommandProcessing->output();
        CommandProcessing->set_handler(std::make_unique<BulkDynamicHandler>(1));
    }
    else
    {
        CommandProcessing->push(data);
        --m_bulkSize;
    }
}

bool BulkEndHandler::done(CommandProcessing* /*CommandProcessing*/)
{
    return true;
}

void BulkEndHandler::read(CommandProcessing* /*CommandProcessing*/)
{
}

} // namespace cmd