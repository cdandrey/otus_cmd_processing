#pragma once

#include <string>
#include <memory>

namespace cmd
{

class ICmdHandler;

class CmdProcessing
{
    public:
        using ICmdHandlerPtr = std::unique_ptr<ICmdHandler>;

        explicit CmdProcessing(int bulkSize = 0);
        void exec();
        void set_handler(ICmdHandlerPtr handler);
        void push(const std::string &cmd);
        void output();
        std::tuple<bool,std::string> read() const;
        int bulkSize() const;

    private:
        ICmdHandlerPtr m_handler;
        std::string m_cmds;
        int m_bulkSize;
};

} // namespace cmd