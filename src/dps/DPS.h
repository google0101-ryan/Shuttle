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
    void Blank(int frames);
    void BlankIDP(int idp, int frames);
    // 0 - Left keyboard, 1 - right keyboard, 2 - rear keyboard
    void SendKey(int kbIdx, int key);

    void UpdateIDPs(GPC* caller);
    void SetBFSEnable(bool bfs);
    void SetKB1(bool crt3);
    void SetKB2(bool crt3);

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
    // Whenever we transition to a new major mode, simulate loading time by blanking for a few frames
    int blankFrames[4];

    bool kb1, kb2;

    static DPS* instance;
};