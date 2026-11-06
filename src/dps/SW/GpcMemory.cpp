#include "GpcMemory.h"
#include <dps/SW/SWUtil.h>

static bool IsGPCTargeted(int gpc, int mask)
{
    return (mask >> (gpc-1)) & 1;
}

GpcMemory::GpcMemory()
{
    // Load MC1 (OPS1 & 6) by default
    editing = mc1;

    // Make sure the freeze-dry section stays cleared
    mcToBeStored = -1;
    storedMC = -1;
    targetStoreGPC = -1;
}

void GpcMemory::Draw(MEDWindow *surf)
{
    surf->SetDrawColor(COLOR_DPS_NORMAL);

    SWUtil::DrawCommonHeader(parent, surf);

    // MEM/BUS CONFIG section
    surf->DrawText(1, 2, "MEM/BUS CONFIG");
    surf->DrawText(1, 3, "1 CONFIG");
    surf->DrawTextUnderline(10, 3, "%2d", editing.num);
    surf->DrawText(12, 3, "(%s%01d)", editing.gnc ? "G" : "S", editing.index);
    surf->DrawText(1, 4, "2 GPC");

    for (int i = 0; i < 5; i++)
    {
        surf->DrawTextUnderline(7 + (i*2), 4, "%d", IsGPCTargeted(i+1, editing.targetMask) ? i+1 : 0);
    }
    surf->DrawText(2, 6, "STRING");
    for (int i = 0; i < 4; i++)
    {
        surf->DrawText(9, 6+i, "%d %2d", i+1, i+7);
        surf->DrawTextUnderline(14, 6+i, "%d", editing.nbat.string[i]);
    }
    surf->DrawText(4, 10, "PL 1/2 11");
    surf->DrawTextUnderline(14, 10, "%d", editing.nbat.pl);

    surf->DrawText(5, 12, "CRT");
    for (int i = 0; i < 4; i++)
    {
        surf->DrawText(9, 12+i, "%d %02d", i+1, i+12, editing.nbat.crt[i]);
        surf->DrawTextUnderline(14, 12+i, "%d", editing.nbat.crt[i]);
    }
    surf->DrawText(2, 17, "LAUNCH");
    for (int i = 0; i < 2; i++)
    {
        surf->DrawText(9, 17+i, "%d %02d", i+1, i+16);
        surf->DrawTextUnderline(14, 17+i, "%d", editing.nbat.launch[i]);
    }
    surf->DrawText(6, 19, "MM");
    for (int i = 0; i < 2; i++)
    {
        surf->DrawText(9, 19+i, "%d %02d", i+1, i+18);
        surf->DrawTextUnderline(14, 19+i, "%d", editing.nbat.mm[i]);
    }

    // READ/WRITE section
    surf->DrawText(18, 2, "READ/WRITE");
    if (parent->GetMM()->GetNum() == 0) // OPS 000
        surf->DrawText(30, 2, "000");
    else
        surf->DrawText(30, 2, editing.gnc ? "GNC" : "SM");
    surf->DrawText(19, 3, "DATA 20   BIT SET 22   SEQ ID 24");
    surf->DrawText(19, 4, "CODE 21   BIT RST 23   WRITE  25");
    surf->DrawText(19, 5, "26 ENG UNITS        HEX 27");
    surf->DrawText(19, 6, "ADD ID   DESIRED   ACTUAL");
    for (int i = 0; i < 6; i++)
    {
        surf->DrawText(18, 7+i, "%2d %s  %2d %s", 28+i*2, 
            i == 0 ? "_____" : "     ",
            29+i*2,
            i == 0 ? "_____" : "     ");
    }

    // MEMORY DUMP section
    surf->DrawText(18, 14, "MEMORY DUMP");
    surf->DrawText(19, 15, "40 START ID  _____");
    surf->DrawText(19, 16, "41 NO WORDS  ______");
    surf->DrawText(19, 17, "42 WDS/FRAME ___");
    surf->DrawText(19, 18, "DUMP 43");

    // STORE section
    surf->DrawText(38, 14, "STORE   MC=");
    if (storedMC != -1)
    {
        surf->DrawTextUnderline(49, 14, "%02d", storedMC);
    }
    surf->DrawText(39, 15, "45 CONFIG");
    if (mcToBeStored == -1)
    {
        surf->DrawTextUnderline(49, 15, "  ");
    }
    else
    {
        surf->DrawTextUnderline(49, 15, "%02d", mcToBeStored);
    }
    surf->DrawText(39, 16, "46 GPC");
    if (targetStoreGPC == -1)
    {
        surf->DrawTextUnderline(46, 16, " ");
    }
    else
    {
        surf->DrawTextUnderline(46, 16, "%d", targetStoreGPC);
    }
    surf->DrawText(39, 17, "STORE 47");

    // DOWNLIST GPC section
    surf->DrawText(19, 20, "44 DOWNLIST GPC _");
    surf->DrawText(21, 21,   "OPS 0 ENA 49");
    surf->DrawText(19, 23, "ERR LOG RESET 48");

    // OPS 3 section
    surf->DrawText(1, 22, "OPS 3 UPLK 50");
    surf->DrawText(1, 23, "OPS 3 INIT 51");

    // MM AREA section
    surf->DrawText(38, 20, "MM AREA");
    surf->DrawText(39, 21, "PL  52 _");
    surf->DrawText(39, 22, "GNC 53 _");
    surf->DrawText(39, 23, "SM  54 _");

    // lines
    surf->SetDrawColor(COLOR_DPS_NORMAL, 255);
    // line dividing the bus numbers from item numbers
    // STRING 1 |  7 1
    surf->DrawLine(105, 84, 105, 298);
    // line splitting off bus config from ops 3 config
    surf->DrawLine(10, 298, 162, 298);
    // line seperating bus config + ops 3 from right side of display
    surf->DrawLine(162, 28, 162, 336);
    // line seperating the read/write section from the mem dump section
    surf->DrawLine(162, 189, 510, 189);
    // line separating mem dump from downlist
    surf->DrawLine(162, 273, 510, 273);
    // line separating mem dump from store
    surf->DrawLine(380, 189, 380, 336);
}

bool GpcMemory::CanTransition(int newMM)
{
    newMM /= 100;
    return parent->GetMC().supportedOps[0] == newMM || 
        parent->GetMC().supportedOps[1] == newMM ||
        newMM == 0;
}

bool GpcMemory::ExecuteItem(ItemCommand &cmd)
{
    switch (cmd.item)
    {
    case 1:
        return SwitchMC(cmd.val);
    case 7 ... 10:
        editing.nbat.string[cmd.item - 7] = cmd.val;
        return true;
    case 11:
        editing.nbat.pl = cmd.val;
        return true;
    case 12 ... 15:
        editing.nbat.crt[cmd.item - 12] = cmd.val;
        return true;
    case 16 ... 17:
        editing.nbat.launch[cmd.item - 16] = cmd.val;
        return true;
    case 18 ... 19:
        editing.nbat.mm[cmd.item - 18] = cmd.val;
        return true;
    }

    return false;
}

bool GpcMemory::SwitchMC(int mc)
{
    mc--;
    if (mc < 0 || mc > 4)
        return false;

    editing = GetConfig(mc);

    return true;
}
