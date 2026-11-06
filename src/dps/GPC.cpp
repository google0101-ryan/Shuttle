#include "GPC.h"
#include <dps/MemoryConfig.h>
#include <dps/DPS.h>
#include <dps/IDP.h>

void GPC::Init(int id)
{
    this->id = id;

    mc = mc1;

    if (id == 5)
        isBFS = true;
    else
        isBFS = false;

    if (isBFS)
        curMM = &bfsMem;
    else
        curMM = &ops0;
    curSpec = nullptr;
    curMM->SetParent(this);

    time.Init();
    internalTime.Init();
    internalTime.Unpause();
}

void GPC::Tick()
{
    if (curSpec)
        curSpec->Tick();
    curMM->Tick();
}

void GPC::SetParent(IDP *idp)
{
    this->idp = idp;
}

void GPC::Liftoff()
{
    if (curMM->GetNum() == 101)
    {
        ((AscentTrajectory*)curMM)->Liftoff();
    }
}

bool GPC::OpsCommand(int mm)
{
    mc = ops0.GetMC();
    // Update global OPS
    SetConfig(mc.num-1, mc);
    // Tell the DPS system that the NBAT has changed
    DPS::Instance()->UpdateIDPs();

    if (mm == curMM->GetNum())
        return true;

    if (!curMM->CanTransition(mm))
        return false;

    if (!isBFS && curMM != &ops0 && !ops0.CanTransition(mm))
        return false;

    if (isBFS)
        return SwitchBFSMM(mm);
    else
        return SwitchPASSMM(mm);
}

Page *GPC::GetCurPage()
{
    if (curSpec)
        return curSpec;
    return curMM;
}

bool GPC::SwitchBFSMM(int mm)
{
    switch (mm)
    {
    case 0:
        curMM = &bfsMem;
        break;
    case 101:
    case 102:
        curMM = &bfsMM101;
        break;
    default:
        printf("Transition to unknown BFS MM %d\n", mm);
        return false;
    }

    curMM->SetParent(this);
    return true;
}

bool GPC::SwitchPASSMM(int mm)
{
    switch (mm)
    {
    case 0:
        curMM = &ops0;
        break;
    case 101:
    case 102:
        curMM = &mm101;
        break;
    default:
        printf("Transition to unknown PASS MM %d\n", mm);
        return false;
    }

    curMM->SetParent(this);
    return true;
}
