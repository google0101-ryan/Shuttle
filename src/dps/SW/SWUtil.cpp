#include "SWUtil.h"

void SWUtil::DrawCommonHeader(GPC *gpc, MEDWindow *window)
{
    char specBuf[4] = {"   "};
    if (gpc->GetSpec())
    {
        sprintf(specBuf, "%03d", gpc->GetSpec()->GetNum());
    }

    char dispBuf[4] = { "   " };
    if (gpc->GetDisp())
    {
        sprintf(dispBuf, "%03d", gpc->GetDisp()->GetNum());
    }

    window->DrawText(1, 0, " %03d1/%03s/%03s  %-16s     %1d %s", gpc->GetMM()->GetNum(), specBuf, dispBuf, gpc->GetCurPage()->GetTitle(), gpc->GetID(), gpc->GetTime()->GetTimeString().c_str());
    window->DrawText(39, 1, "000/00:00:00");
    if (gpc->IsBFS())
    {
        window->YellowFont();
        window->DrawText(35, 1, "BFS");
        window->DPSFont();
    }
}