#pragma once

class CmdProcessing;

class ICmdHandler
{
    public:
        using CmdProcessingPtr = std::shared_ptr<CmdProcessing>;

        virtual ~ICmdHandler() = 0;
        virtual bool done(CmdProcessingPtr cmdProcessing) = 0;
        virtual void read(CmdProcessingPtr cmdProcessing) = 0;
};

class BulkBeginHandler : public ICmdHandler
{
    public:
        virtual bool done(CmdProcessingPtr cmdProcessing);
        virtual void read(CmdProcessingPtr cmdProcessing);

    private:
        int m_sizeBulk;
};

class BulkStaticHandler : public ICmdHandler
{
    public:
        explicit BulkStaticHandler(int bulkSize);
        bool done(CmdProcessingPtr cmdProcessing) override;
        void read(CmdProcessingPtr cmdProcessing) override;

    private:
        int m_bulkSize;
};

class BulkDynamicHandler : public ICmdHandler
{
    public:
        explicit BulkDynamicHandler(int countOpenBulk);
        bool done(CmdProcessingPtr cmdProcessing) override;
        void read(CmdProcessingPtr cmdProcessing) override;

    private:
        int m_countOpenBulk;
};

class BulkEndHandler : public ICmdHandler
{
    public:
        bool done(CmdProcessingPtr cmdProcessing) override;
        void read(CmdProcessingPtr cmdProcessing) override;
};