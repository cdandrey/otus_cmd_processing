#pragma once

class CmdProcessing;

class ICmdHandler
{
    using CmdProcessingPtr = std::weak_ptr<CmdProcessing>;

    public:
        virtual ~ICmdHandler() = 0;
        virtual bool done(CmdProcessingPtr cmdProcessing) = 0;
        virtual void read(CmdProcessingPtr cmdProcessing) = 0;
};

class BulkBeginHandler : public ICmdHandler
{
    private:
        int m_sizeBulk;
};

class BulkStaticHandler : public ICmdHandler
{
    private:
        int m_bulkSize;

    public:
        explicit BulkSizeHandler(int bulkSize);
        bool done(CmdProcessingPtr cmdProcessing) override;
        void read(CmdProcessingPtr cmdProcessing) override;
};

class BulkDynamicHandler : public ICmdHandler
{

    private:
        m_countOpenBulk;

    public:
        explicit BulkDynamicHandler(int countOpenBulk);
        bool done(CmdProcessingPtr cmdProcessing) override;
        void read(CmdProcessingPtr cmdProcessing) override;
};

class BulkEndHandler : public ICmdHandler
{
    public:
        bool done(CmdProcessingPtr cmdProcessing) override;
        void read(CmdProcessingPtr cmdProcessing) override;
}