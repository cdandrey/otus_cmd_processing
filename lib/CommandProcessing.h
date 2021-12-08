#pragma once

#include <string>
#include <memory>

namespace cmd
{

class AbstractCommandHandler;
using AbstractCommandHandlerPtr = std::unique_ptr<AbstractCommandHandler>;

class CommandProcessing
{
public:

    explicit CommandProcessing(int bulkSize = 0);
    void exec();
    void set_handler(AbstractCommandHandlerPtr&& handler);
    void push(const std::string& cmd);
    void output();
    std::tuple<bool, std::string> read() const;
    int bulkSize() const;

private:
    AbstractCommandHandlerPtr m_handler;
    std::string m_cmds;
    int m_bulkSize;
};

} // namespace cmd