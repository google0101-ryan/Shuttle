#include "BFS_MM101.h"
#include <dps/SW/SWUtil.h>
#include <dps/DPS.h>

void BFS_LaunchTrajectory::Draw(MEDWindow *surf)
{
    SWUtil::DrawCommonHeader(parent, surf);

    surf->DrawText(8, 8, "T 100");
    surf->DrawText(8, 10, "R 000");
    surf->DrawText(8, 11, "P 000");
    surf->DrawText(8, 12, "Y 000");

    surf->DrawText(11, 23, "70");
    surf->DrawText(19, 20, "60");
    surf->DrawText(24, 18, "50");
    surf->DrawText(31, 15, "40");

    surf->SetDrawColor(COLOR_DPS_NORMAL, 255);
    surf->DrawLine(78, 324, 116, 317);
    surf->DrawLine(116, 317, 159, 302);
    surf->DrawLine(159, 302, 217, 257);
    surf->DrawLine( 217, 257, 355, 174 );
	surf->DrawLine( 355, 174, 438, 119 );
	surf->DrawLine( 438, 119, 455, 97 );
	surf->DrawLine( 455, 97, 471, 58 );

	surf->DrawLine( 322, 189, 322, 200 );
	surf->DrawLine( 254, 230, 254, 241 );
	surf->DrawLine( 196, 267, 196, 278 );
	surf->DrawLine( 116, 313, 116, 324 );

    surf->DrawText(1, 3.5, "KEAS");
    surf->DrawText(1, 5, "500");
    surf->DrawText(1, 8, "400");
    surf->DrawText(1, 11, "300");
    surf->DrawText(1, 14, "200");
    surf->DrawText(1, 17, "100");
    surf->DrawText(3, 20, "0");

    // Vertical scale
    surf->DrawLine(45, 77, 45, 287);
    for (int i = 0; i < 11; i++)
        surf->DrawLine(40, 77 + (i * 21), 45, 77 + (i * 21));

    surf->DrawText(5, 15.5, "STG");
}

const char *BFS_LaunchTrajectory::GetTitle()
{
    int dispId = DPS::Instance()->GetCompool()->Read<int>(DISPLAYTITLE_ID);

    switch (dispId)
    {
    case 1:
        return "LAUNCH TRAJ 1";
    case 2:
        return "ASCENT TRAJ 1";
    case 3:
        return "  RTLS TRAJ 1";
    case 4:
        return "   ATO TRAJ 1";
    default:
        return "XXXXXX TRAJ 1";
    }
}

bool BFS_LaunchTrajectory::CanTransition(int newMM)
{
    return hasLaunched && newMM == 103;
}
