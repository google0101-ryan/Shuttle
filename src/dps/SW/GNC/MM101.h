#pragma once

#include <dps/SW/Page.h>

class AscentTrajectory : public Page
{
public:
    AscentTrajectory();

    void Liftoff();

    virtual void Draw(MEDWindow* surf);
    virtual int GetNum() { return hasLaunched ? 102 : 101; }
    virtual const char* GetTitle();
    virtual bool CanTransition(int newMM);
private:
    bool hasLaunched;
};