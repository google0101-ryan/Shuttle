#pragma once

#include <dps/SW/Page.h>

class BFSMemory : public Page
{
public:
    BFSMemory();
    virtual ~BFSMemory() {}
    
    virtual void Tick();

    virtual void Draw(MEDWindow* surf);
    virtual int GetNum() { return 0; }
    virtual const char* GetTitle() { return "BFS MEMORY"; }

    virtual bool ExecuteItem(ItemCommand& cmd);
    // BFS is much more limited
    virtual bool CanTransition(int newMM) { return newMM == 101; }
private:
    bool isXferingPASS;
    double xferStartTime;
};