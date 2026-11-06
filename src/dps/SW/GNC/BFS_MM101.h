#pragma once

#include <ui/MEDWindow.h>
#include <dps/SW/Page.h>

class BFS_LaunchTrajectory : public Page
{
public:
    virtual void Draw(MEDWindow* surf);
    virtual int GetNum() { return hasLaunched ? 102 : 101; }
    virtual const char* GetTitle();
    virtual bool CanTransition(int newMM);
private:
    bool hasLaunched;
};