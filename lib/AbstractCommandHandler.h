#pragma once

namespace cmd
{

class CommandProcessing;

class AbstractCommandHandler
{
public:

    virtual ~AbstractCommandHandler() {};
    virtual bool done(CommandProcessing* CommandProcessing) = 0;
    virtual void read(CommandProcessing* CommandProcessing) = 0;
};

class BulkBeginHandler : public AbstractCommandHandler
{
public:
    virtual bool done(CommandProcessing* CommandProcessing);
    virtual void read(CommandProcessing* CommandProcessing);

private:
    int m_sizeBulk;
};

class BulkStaticHandler : public AbstractCommandHandler
{
public:
    explicit BulkStaticHandler(int bulkSize);
    bool done(CommandProcessing* CommandProcessing) override;
    void read(CommandProcessing* CommandProcessing) override;

private:
    int m_bulkSize;
};

class BulkDynamicHandler : public AbstractCommandHandler
{
public:
    explicit BulkDynamicHandler(int countOpenBulk);
    bool done(CommandProcessing* CommandProcessing) override;
    void read(CommandProcessing* CommandProcessing) override;

private:
    int m_countOpenBulk;
};

class BulkEndHandler : public AbstractCommandHandler
{
public:
    bool done(CommandProcessing* CommandProcessing) override;
    void read(CommandProcessing* CommandProcessing) override;
};

} // namespace cmd