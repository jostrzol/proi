#pragma once

class IHelperWorker
{
public:
    virtual bool IsBusy() = 0;
    virtual void SetBusy(bool val) = 0;
};
