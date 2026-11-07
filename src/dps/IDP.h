#pragma once

#include <ui/MEDWindow.h>
#include <ui/Keyboard.h>
#include <queue>
#include <string>

class GPC;

struct ItemCommand
{
    int item;
    int val;
};

class IDP
{
public:
    void Init(int id);
    void Tick();
    void Draw(MEDWindow* surf);
    void DrawKB1Ind(MEDWindow* surf);
    void DrawKB2Ind(MEDWindow* surf);

    void SetGPC(GPC* gpc);
    GPC* GetGPC();

    void SendKey(int key);
    void AddError(GPC* gpc, const char* msg, const char* msg2);
private:
    void ParseItemCommand();
    void ParseOpsCommand();
    void ParseSpecCommand();
    void ParseGpcCrtCommand();

    int GetFlashingEntry();
private:
    GPC* gpc;
    int id;

    int inputLine[100];
    int inputLineLen;
    bool inputError;
    bool lineComplete = false;
    bool processed = false;
    std::queue<std::string> errorMsgQ;
};