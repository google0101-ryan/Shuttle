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

    for (int i = 0; i < 4; i++)
        blankFrames[i] = 0;

    bfsEnabled = false;
    kb1 = false;
    kb2 = false;
    isInLiftoff = false;
}

void DPS::Tick()
{
    for (int i = 0; i < 4; i++)
        idp[i].Tick();
#if 0
    if (!isInLiftoff && gpcs[0].GetTime()->GetTimeS() > 60)
    {
        Liftoff();
    }
    else if (isInLiftoff)
    {
        switch ((int)gpcs[0].GetTime()->GetTimeS())
        {
        case 115:
            pool.Write<bool>(PC_LT_50, true);
            break;
        case 120:
            pool.Write<bool>(PC_LT_50, false);
            break;
        }
    }
#endif
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
    if (blankFrames[idx] > 0)
    {
        blankFrames[idx]--;
        return;
    }

    idp[idx].Draw(surf);

    if (idx == 0)
    {
        if (!kb1)
            idp[idx].DrawKB1Ind(surf);
    }
    else if (idx == 1)
    {
        if (!kb2)
            idp[idx].DrawKB2Ind(surf);
    }
    else if (idx == 2)
    {
        if (kb1)
            idp[idx].DrawKB1Ind(surf);
        if (kb2)
            idp[idx].DrawKB2Ind(surf);
    }
}

void DPS::Blank(int frames)
{
    for (int i = 0; i < 4; i++)
        blankFrames[i] = frames;
}

void DPS::BlankIDP(int idp, int frames)
{
    blankFrames[idp] = frames + (rand() % 10);
}

void DPS::SendKey(int kbIdx, int key)
{
    // TODO: Left and right can optionally talk to CRT3 instead of 1 and 2

    switch (kbIdx)
    {
    case 0:
        if (kb1)
            idp[2].SendKey(key);
        else
            idp[0].SendKey(key);
        break;
    case 1:
        if (kb2)
            idp[2].SendKey(key);
        else
            idp[1].SendKey(key);
        break;
    case 2:
        idp[3].SendKey(key);
        break;
    }
}

void DPS::UpdateIDPs(GPC* caller)
{
    // TODO: redundant set evaluation
    auto mc = caller->GetMC();

    // Remap CRTs
    idp[0].SetGPC(mc.nbat.crt[0] != 0 ? &gpcs[mc.nbat.crt[0]-1] : nullptr);
    idp[1].SetGPC(mc.nbat.crt[1] != 0 ? &gpcs[mc.nbat.crt[1]-1] : nullptr);
    // Don't remap CRT 3 if the BFS switch is on
    if (!bfsEnabled)
        idp[2].SetGPC(mc.nbat.crt[2] != 0 ? &gpcs[mc.nbat.crt[2]-1] : nullptr);
    idp[3].SetGPC(mc.nbat.crt[3] != 0 ? &gpcs[mc.nbat.crt[3]-1] : nullptr);
    // Broadcast changes to all other GPCs
    for (int i = 0; i < 5; i++)
    {
        if (i == caller->GetID())
            continue;
        gpcs[i].UpdateMC(caller->GetMC());
    }
}

void DPS::SetBFSEnable(bool bfs)
{
    if (bfs != bfsEnabled)
        BlankIDP(2, 10);

    bfsEnabled = bfs;

    auto mc = gpcs[0].GetMC();

    if (bfs)
        idp[2].SetGPC(&gpcs[4]);
    else
        idp[2].SetGPC(mc.nbat.crt[2] != 0 ? &gpcs[mc.nbat.crt[2]-1] : nullptr);
}

void DPS::SetKB1(bool crt3)
{
    kb1 = crt3;
}

void DPS::SetKB2(bool crt3)
{
    kb2 = crt3;
}

DPS *DPS::Instance()
{
    return instance;
}
