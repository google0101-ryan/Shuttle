#include <dps/SW/GNC/GNCSpec18.h>
#include <dps/SW/SWUtil.h>

void GNCSysSumm1::Draw(MEDWindow* surf)
{
    SWUtil::DrawCommonHeader(parent, surf);

    surf->SetDrawColor(COLOR_DPS_NORMAL);

    surf->DrawText(1, 3, "RCS  JETISOL");
    surf->DrawText(1, 4, "MANFFAILVLV");
    surf->DrawLine(10, 72, 130, 72);
    surf->DrawText(3, 5, "F");
    surf->DrawLine(10, 142, 130, 142);
    surf->DrawText(3, 10, "L");
    surf->DrawLine(10, 212, 130, 212);
    surf->DrawText(3, 15, "R");
    for (int i = 0; i < 15; i++)
    {
        surf->DrawText(4, 5 + i, "%d", (i%5)+1);
        surf->DrawText(10, 5 + i, "OP");
    }

    surf->DrawText(15, 4, "SURF     POS   MOM");
    surf->DrawLine(150, 72, 330, 72);
    surf->DrawText(15, 5, "L OB    000.0  00");
    surf->DrawText(15, 6, "  IB    000.0  00");
    surf->DrawText(15, 7, "R IB    000.0  00");
    surf->DrawText(15, 8, "  OB    000.0  00");
    surf->DrawText(15, 9, "AIL     000.0");
    surf->DrawText(15, 10, "SPD BRK 000.0");
    surf->DrawText(15, 11, "BDY FLP 000.0");

    surf->DrawText(35, 4, "DPS    1 2 3 4 5");
    surf->DrawLine(350, 72, 510, 72);
    surf->DrawText(38, 5, "GPC");
    surf->DrawText(35, 6, "MDM FF");
    surf->DrawText(39, 7, "FA");

    surf->DrawText(35, 10, "FCS CH 1 2 3 4");
    surf->DrawLine(350, 156, 510, 156);

    surf->DrawText(35, 14, "NAV    1 2 3 4");
    surf->DrawLine(350, 212, 510, 212);
    surf->DrawText(35, 15, "  IMU");
    surf->DrawText(35, 16, "  ACC");
    surf->DrawText(35, 17, "  RGA");
    surf->DrawText(35, 18, "  GPS");
    surf->DrawText(35, 19, "  MLS");
    surf->DrawText(35, 20, "  ADTA");

    surf->DrawText(17, 16, "CNTLR  1 2 3");
    surf->DrawLine(170, 240, 290, 240);
    surf->DrawText(17, 17, "RHC  L ");
    surf->DrawText(17, 18, "     R ");
    surf->DrawText(17, 19, "     A ");
    surf->DrawText(17, 20, "THC  L ");
    surf->DrawText(17, 21, "     A ");
    surf->DrawText(17, 22, "SBTC L ");
    surf->DrawText(17, 23, "     R ");
}