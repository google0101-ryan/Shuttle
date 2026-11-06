#pragma once

#include <ui/MEDWindow.h>
#include <dps/IDP.h>
#include <dps/GPC.h>
#include <dps/Compool.h>

class DPS
{
public:
    DPS();
    void Init();

    // Called once per frame
    void Tick();

    // TEMP: Simulate a liftoff
    // TODO: Add a message pool that each GPC can read from, and read/write signals like LIFTOFF from there
    void Liftoff();

    void Draw(int idx, MEDWindow* surf);
    // 0 - Left keyboard, 1 - right keyboard, 2 - rear keyboard
    void SendKey(int kbIdx, int key);

    void UpdateIDPs();
    void SetBFSEnable(bool bfs);

    GPC* GetGPC(int i) { return &gpcs[i]; }
    IDP* GetIDP(int i) { return &idp[i]; }
    Compool* GetCompool() { return &pool; }

    static DPS* Instance();
private:
    IDP idp[4];
    GPC gpcs[5];
    Compool pool;

    bool bfsEnabled;
    bool isInLiftoff;

    static DPS* instance;
};