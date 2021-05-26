#pragma once

class IHelperWorker
{
public:
    virtual void SetBusy(bool val) = 0;
    virtual bool GetBusy() = 0;
};
