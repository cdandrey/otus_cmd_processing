#include <iostream>

#include "cmd_processing.h"
#include "cmd_handler.h"

namespace cmd
{

CmdProcessing::CmdProcessing(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

void CmdProcessing::exec()
{
    m_handler = ICmdHandlerPtr{new BulkBeginHandler()};

    while (!m_handler->done(this)) {
        m_handler->read(this);
    }
}

void CmdProcessing::set_handler(ICmdHandlerPtr handler)
{
    m_handler = std::move(handler);
}

void CmdProcessing::push(const std::string& cmd)
{
    m_cmds.append(" ");
    m_cmds.append(cmd);
    m_cmds.append(",");
}

void CmdProcessing::output()
{
    if (!m_cmds.empty()) {
        m_cmds.pop_back();  // removed ','
        std::cout << "bulk:" << m_cmds << std::endl;
        m_cmds.clear();
    }
}

std::tuple<bool,std::string> CmdProcessing::read() const
{
    std::string data;
    bool result = false;
    if (std::getline(std::cin,data)) {
        result = true;
    };
    return {result,data};
}

int CmdProcessing::bulkSize() const
{
    return m_bulkSize;
}

}