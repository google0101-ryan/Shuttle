#pragma once

#include <dps/SW/GpcMemory.h>
#include <dps/SW/BfsMemory.h>
#include <dps/SW/GNC/MM101.h>
#include <dps/SW/GNC/BFS_MM101.h>
#include <dps/Timer.h>

class IDP;

class GPC
{
public:
    void Init(int id);
    void Tick();
    void SetParent(IDP* idp);
    IDP* GetParent() { return idp; }

    void Liftoff();

    void PreOpsCommand();
    bool OpsCommand(int mm);
    bool GoToSpec(int spec);

    Page* GetCurPage();
    Time* GetTime() { return &time; }
    Time* GetInternalTime() { return &internalTime; }

    Page* GetSpec() { return curSpec;}
    Page* GetMM() { return curMM; }

    int GetID() { return id; }

    void SetMC(MemoryConfig& mc) { this->mc = mc; }
    MemoryConfig& GetMC() { return mc; }
    void UpdateMC(MemoryConfig& mc) { this->mc = mc; ops0.GetMC() = mc; }

    bool IsBFS() { return isBFS; }
private:
    bool SwitchBFSMM(int mm);
    bool SwitchPASSMM(int mm);
private:
    Page* curMM;
    Page* curSpec;
    IDP* idp;

    GpcMemory ops0;
    AscentTrajectory mm101;

    BFSMemory bfsMem;
    BFS_LaunchTrajectory bfsMM101;

    Time time;
    Time internalTime; // Used independently of the MET timer for tracking things like how long to leave an asterisk on one of the screens

    int id;
    MemoryConfig mc;
    bool isBFS;
};