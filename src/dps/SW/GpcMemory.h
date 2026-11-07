#pragma once

#include <SW/Page.h>
#include <dps/MemoryConfig.h>

class GpcMemory : public Page
{
public:
    GpcMemory();
    virtual ~GpcMemory() {}

    MemoryConfig& GetMC() { return editing; }

    virtual void Tick();
    virtual void Draw(MEDWindow* surf);
    virtual int GetNum() { return 0; }
    virtual const char* GetTitle() { return "GPC MEMORY"; }
    virtual bool CanTransition(int newMM);

    virtual bool ExecuteItem(ItemCommand& cmd);
private:
    bool SwitchMC(int mc);
private:
    MemoryConfig editing; // The current MC being edited
    int targMask;
    int mcToBeStored;
    int storedMC;
    int targetStoreGPC;
    bool storingMC;
    double storeTime;
};