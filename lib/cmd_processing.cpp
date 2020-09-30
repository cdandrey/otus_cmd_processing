#include <iostream>
#include <algorithm>
#include "cmd_processing.h"
#include "cmd_handler.h"

void CmdProcessing::CmdProcessing(int bulkSize)
    : m_bulkSize(bulkSize)
{
}

void CmdProcessing::exec() const
{
    m_cmds = "bulk: ";
    m_handler = std::make_unique<BulkBeginHandler>();

    while (!m_handler->done(this)) {
        m_handler->read(this);
    }
}

void CmdProcessing::set_state(ICmdHandlerPtr handler)
{
    m_handler = std::move(handler);
}

void CmdProcessing::push(const std::string& cmd)
{
    m_cmds.emplace_back({" ",cmd,","});
}

void CmdProcessing::pull()
{
    std::cout << m_cmds << std::endl;

    m_cmds = "bulk: ";
}

std::tuple<bool,std::string> CmdProcessing::read() const
{
    std::string data;
    const auto result = std::static_cast<bool>(std::getline(std::cin,data));
    return {result,data};
}

int CmdProcessing::bulkSize() const
{
    return m_bulkSize;
}