#pragma once

class IHelperWorker
{
public:
    // Set worker busy anwsering a question
    virtual void SetBusy(bool val) = 0;
    // Return if worker is busy anwsering a question
    virtual bool GetBusy() = 0;
};
