#include <dps/SW/GNC/BFSSpec18.h>
#include <dps/SW/SWUtil.h>

void BFSSysSumm1::Draw(MEDWindow* surf)
{
    SWUtil::DrawCommonHeader(parent, surf);

    surf->SetDrawColor(COLOR_DPS_NORMAL);

    surf->DrawText(6, 4, "SURF     POS   MOM");
    surf->DrawLine(60, 72, 240, 72);
    surf->DrawText(6, 5, "L OB    000.0  00");
    surf->DrawText(6, 6, "  IB    000.0  00");
    surf->DrawText(6, 7, "R IB    000.0  00");
    surf->DrawText(6, 8, "  OB    000.0  00");
    surf->DrawText(6, 9, "AIL     000.0");
    surf->DrawText(6, 10, "RUD     000.0");
    surf->DrawText(6, 11, "SPD BRK 000.0");
    surf->DrawText(6, 12, "BDY FLP 000.0");

    surf->DrawText(31, 4, "DPS    1 2 3 4 5");
    surf->DrawLine(310, 72, 470, 72);
    surf->DrawText(31, 5, "MDM FF");
    surf->DrawText(35, 6, "FA");
    surf->DrawText(35, 7, "PL");

    surf->DrawText(31, 14, "NAV    1 2 3 4");
    surf->DrawLine(310, 212, 450, 212);
    surf->DrawText(31, 15, "IMU");
    surf->DrawText(31, 16, "GPS");
    surf->DrawText(31, 17, "ADTA");

    surf->DrawText(3, 14, "MPS         L     C     R");
    surf->DrawLine(40, 212, 305, 212);
    surf->DrawLine(305, 212, 305, 262);
    surf->DrawText(3, 15, "HE TK P   0000  0000  0000");
    surf->DrawText(3, 16, "  REG P A 0000  0000  0000");
    surf->DrawText(3, 17, "        B 0000  0000  0000");
    surf->DrawText(3, 18, "  dP/dT    000   000   000");
    surf->DrawText(3, 20, "ULL P LH2 00.0  00.0  00.0");
    surf->DrawText(9, 21, "LO2 00.0  00.0  00.0");
    surf->DrawText(3, 23, "GH2 OUT P 0000  0000   0000");
    surf->DrawText(3, 24, "GO2 OUT T 0000  0000   0000");

    surf->DrawLine(305, 262, 500, 262);
    surf->DrawText(31, 19, "MPS PNEU HE P");
    surf->DrawText(36, 20, "TK   0000");
    surf->DrawText(36, 21, "REG  0000");
    surf->DrawText(36, 22, "ACUM 0000");
    surf->DrawText(31, 23, "MANF P LH2 000");
    surf->DrawText(38, 24, "LO2 000");
}