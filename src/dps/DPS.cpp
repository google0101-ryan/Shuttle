#include "DPS.h"

DPS* DPS::instance = nullptr;

DPS::DPS()
{
    instance = this;
}

void DPS::Init()
{
    for (int i = 0; i < 5; i++)
    {
        gpcs[i].Init(i+1);
        gpcs[i].GetTime()->Unpause();
        if (i < 4)
            idp[i].Init(i+1);
    }

    idp[0].SetGPC(&gpcs[0]);
    idp[1].SetGPC(&gpcs[1]);
    idp[2].SetGPC(&gpcs[2]);
    idp[3].SetGPC(&gpcs[3]);

    // COMPOOL setup
    pool.Write(DISPLAYTITLE_ID, 1);
}

void DPS::Tick()
{
    for (int i = 0; i < 4; i++)
        idp[i].Tick();
}

void DPS::Liftoff()
{
    pool.Write(DISPLAYTITLE_ID, 2);
    // Command engines to 100%
    pool.Write(K_CMD, 100);
    // Reset all timers to 0
    for (int i = 0; i < 5; i++)
    {
        gpcs[i].GetTime()->Init();
        gpcs[i].GetTime()->Unpause();
    }

    isInLiftoff = true;

    for (int i = 0; i < 5; i++)
        gpcs[i].Liftoff();
}

void DPS::Draw(int idx, MEDWindow *surf)
{
    idp[idx].Draw(surf);
}

void DPS::SendKey(int kbIdx, int key)
{
    // TODO: Left and right can optionally talk to CRT3 instead of 1 and 2

    switch (kbIdx)
    {
    case 0:
        idp[0].SendKey(key);
        break;
    case 1:
        idp[2].SendKey(key);
        break;
    case 2:
        idp[3].SendKey(key);
        break;
    }
}

void DPS::UpdateIDPs()
{
    // TODO: redundant set evaluation
    auto mc = gpcs[0].GetMC();

    // Remap CRTs
    idp[0].SetGPC(mc.nbat.crt[0] != 0 ? &gpcs[mc.nbat.crt[0]-1] : nullptr);
    idp[1].SetGPC(mc.nbat.crt[1] != 0 ? &gpcs[mc.nbat.crt[1]-1] : nullptr);
    // Don't remap CRT 3 if the BFS switch is on
    if (!bfsEnabled)
        idp[2].SetGPC(mc.nbat.crt[2] != 0 ? &gpcs[mc.nbat.crt[2]-1] : nullptr);
    idp[3].SetGPC(mc.nbat.crt[3] != 0 ? &gpcs[mc.nbat.crt[3]-1] : nullptr);
    // Broadcast changes to all other GPCs
    for (int i = 1; i < 5; i++)
    {
        gpcs[i].UpdateMC(gpcs[0].GetMC());
    }
}

void DPS::SetBFSEnable(bool bfs)
{
    bfsEnabled = bfs;

    auto mc = gpcs[0].GetMC();

    if (bfs)
        idp[2].SetGPC(&gpcs[4]);
    else
        idp[2].SetGPC(mc.nbat.crt[2] != 0 ? &gpcs[mc.nbat.crt[2]-1] : nullptr);
}

DPS *DPS::Instance()
{
    return instance;
}
