#pragma once

#include <string>
#include <memory>

class ICmdHandler;

class CmdProcessing
{

    public:
        using ICmdHandlerPtr = std::unique_ptr<ICmdHandler>;

        explicit CmdProcessing(int bulkSize);
        void exec();
        void set_state(ICmdHandlerPtr handler);
        void push(const std::string &cmd);
        void pull();
        std::tuple<bool,std::string> read() const;
        int bulkSize() const;

    private:
        ICmdHandlerPtr m_handler;
        std::string m_cmds;
        int m_bulkSize;

};
