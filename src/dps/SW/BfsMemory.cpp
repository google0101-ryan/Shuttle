#include "BfsMemory.h"

#include <dps/SW/SWUtil.h>

BFSMemory::BFSMemory()
: Page()
{
}

void BFSMemory::Tick()
{
    if (isXferingPASS)
    {
        double elapsed = parent->GetTime()->GetTimeMS() - xferStartTime;

        if (elapsed > 5000)
        {
            xferStartTime = -1;
            isXferingPASS = false;
        }
    }
}

void BFSMemory::Draw(MEDWindow *surf)
{
    SWUtil::DrawCommonHeader(parent, surf);

    // READ/WRITE memory
    surf->DrawText(10, 3, "READ/WRITE");
    surf->DrawText(11, 4, "DATA 1   BIT SET 3   SEQ ID 5");
    surf->DrawText(11, 5, "CODE 2   BIT RST 4   WRITE  6");
    surf->DrawText(11, 6, "7 ENG UNITS ___     HEX 8");
    surf->DrawText(11, 7, "ADD ID   DESIRED   ACTUAL");
    surf->DrawText(11, 8, "9 _____  10 ____");
    for (int i = 0; i < 5; i++)
    {
        surf->DrawText(10, 9 + i, "%02d        %02d", 11 + i * 2, 12 + i * 2);
    }

    // MEMORY DUMP
    surf->DrawText(2, 16, "MEMORY DUMP");
    surf->DrawText(3, 17, "21 START ID   _____");
    surf->DrawText(3, 18, "22 NUMBER WDS ______");
    surf->DrawText(3, 19, "23 WDS/FRAME  ___");
    surf->DrawText(3, 20, "DUMP START/STOP 24");

    // LAUNCH BUS
    surf->DrawText(25, 16, "LAUNCH BUS   1 26  TFL ENA");
    surf->DrawText(38, 17, "2 27      29*");
    surf->DrawText(36, 18, "OFF 28*");
    surf->DrawText(25, 20, "PASS/BFS XFER ENA 25%s", isXferingPASS ? "*" : "");

    // BFS TIME UPDATES
    surf->DrawText(2, 22, "BFS TIME UPDATES    UPDATE 38    MISSION TIME");
    surf->DrawText(3, 23,  "30 GMT d     /  :  :  .          GMT 39");
    surf->DrawText(3, 24,  "34 MET d     /  :  :  .          MET 40*");
    surf->DrawTextUnderline(25, 23, ".");
    surf->DrawTextUnderline(13, 23, "   ");
    surf->DrawTextUnderline(17, 23, "  ");
    surf->DrawTextUnderline(20, 23, "  ");
    surf->DrawTextUnderline(23, 23, "  ");
    surf->DrawTextUnderline(26, 23, "   ");

    surf->SetDrawColor(COLOR_DPS_NORMAL, 255);
    surf->DrawLine(10, 215, 510, 215);
    surf->DrawLine(240, 215, 240, 308);
}

bool BFSMemory::ExecuteItem(ItemCommand &cmd)
{
    switch (cmd.item)
    {
    case 25:
        if (cmd.val != -1)
            return false;
        isXferingPASS = true;
        xferStartTime = parent->GetInternalTime()->GetTimeMS();
        return true;
    default:
        return false;
    }
}
