#pragma once

#include <vector>

class ICmdHandler;

class CmdProcessing
{
    using ICmdHandlerPtr = std::unique_ptr<ICmdHandler>;

    private:
        ICmdHandlerPtr m_handler;
        std::string m_cmds;
        int m_bulkSize;

    public:
        explicit CmdProcessing(int bulkSize);
        void exec(int bulkSize) const;
        void set_state(ICmdHandlerPtr handler);
        void push(const std::string &cmd);
        void pull();
        std::tuple<bool,std::string> read() const;
        int bulkSize() const;
};
