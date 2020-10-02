#pragma once

namespace cmd 
{

class CmdProcessing;

class ICmdHandler
{
    public:
        using ICmdHandlerPtr = CmdProcessing::ICmdHandlerPtr;

        virtual ~ICmdHandler() = 0 {};
        virtual bool done(CmdProcessing* cmdProcessing) = 0;
        virtual void read(CmdProcessing* cmdProcessing) = 0;
};

class BulkBeginHandler : public ICmdHandler
{
    public:
        virtual bool done(CmdProcessing* cmdProcessing);
        virtual void read(CmdProcessing* cmdProcessing);

    private:
        int m_sizeBulk;
};

class BulkStaticHandler : public ICmdHandler
{
    public:
        explicit BulkStaticHandler(int bulkSize);
        bool done(CmdProcessing* cmdProcessing) override;
        void read(CmdProcessing* cmdProcessing) override;

    private:
        int m_bulkSize;
};

class BulkDynamicHandler : public ICmdHandler
{
    public:
        explicit BulkDynamicHandler(int countOpenBulk);
        bool done(CmdProcessing* cmdProcessing) override;
        void read(CmdProcessing* cmdProcessing) override;

    private:
        int m_countOpenBulk;
};

class BulkEndHandler : public ICmdHandler
{
    public:
        bool done(CmdProcessing* cmdProcessing) override;
        void read(CmdProcessing* cmdProcessing) override;
};

} // namespace cmd