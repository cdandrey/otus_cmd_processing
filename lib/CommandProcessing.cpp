#include <iostream>

#include "AbstractCommandHandler.h"
#include "CommandProcessing.h"

namespace cmd
{

CommandProcessing::CommandProcessing(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

void CommandProcessing::exec()
{
    m_handler = std::make_unique<BulkBeginHandler>();

    while (!m_handler->done(this))
    {
        m_handler->read(this);
    }
}

void CommandProcessing::set_handler(AbstractCommandHandlerPtr&& handler)
{
    m_handler = std::move(handler);
}

void CommandProcessing::push(const std::string& cmd)
{
    m_cmds.append(" ");
    m_cmds.append(cmd);
    m_cmds.append(",");
}

void CommandProcessing::output()
{
    if (!m_cmds.empty())
    {
        m_cmds.pop_back(); // removed ','
        std::cout << "bulk:" << m_cmds << std::endl;
        m_cmds.clear();
    }
}

std::tuple<bool, std::string> CommandProcessing::read() const
{
    std::string data;
    bool result = false;
    if (std::getline(std::cin, data))
    {
        result = true;
    };
    return { result, data };
}

int CommandProcessing::bulkSize() const { return m_bulkSize; }

} // namespace cmd