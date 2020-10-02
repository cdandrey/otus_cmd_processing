#include <iostream>
#include <algorithm>
#include "cmd_processing.h"
#include "cmd_handler.h"

CmdProcessing::CmdProcessing(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

void CmdProcessing::exec()
{
    m_cmds = "bulk:";
    m_handler = std::make_unique<BulkBeginHandler>();

    auto thisPtr = std::make_shared<CmdProcessing>(this);

    while (!m_handler->done(thisPtr)) {
        m_handler->read(thisPtr);
    }
}

void CmdProcessing::set_state(ICmdHandlerPtr handler)
{
    m_handler = std::move(handler);
}

void CmdProcessing::push(const std::string& cmd)
{
    m_cmds.append(" ");
    m_cmds.append(cmd);
    m_cmds.append(",");
}

void CmdProcessing::pull()
{
    m_cmds.pop_back();  // removed ','
    std::cout << m_cmds << std::endl;

    m_cmds = "bulk:";
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