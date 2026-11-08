#include "MM101.h"

#include <dps/SW/SWUtil.h>
#include <dps/DPS.h>

AscentTrajectory::AscentTrajectory()
{
    hasLaunched = false;
}

void AscentTrajectory::Liftoff()
{
    hasLaunched = true;
}

void AscentTrajectory::Draw(MEDWindow *surf)
{
    SWUtil::DrawCommonHeader(parent, surf);

    surf->DrawText(8, 6, "CONT ABORT");
    surf->DrawText(9, 7, "3EO BLUE");
    surf->DrawText(2, 8, "2  ARM 2EO BLUE");
    surf->DrawText(2, 9, "4  ABORT");
    surf->DrawText(2, 11, "5 ENA YAW STEER");
    surf->DrawText(2, 13, "6  SERC");
    
    surf->DrawText(39, 18, "THROT");
    if (GetNum() != 101)
        surf->DrawText(45, 18, "%03d", DPS::Instance()->GetCompool()->Read<int>(K_CMD));

    surf->DrawText(19, 23, "7 INH DRP 1EO");

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

    if (GetNum() == 102)
    {
        float altitude = DPS::Instance()->GetCompool()->Read<float>(ORB_ALT);
        float vr = DPS::Instance()->GetCompool()->Read<float>(ORB_VR);

        short stY = (short)(324 - (altitude * 0.00164198));
        short stX = (short)(78 + (vr * 0.0930909));

        surf->SetDrawColor(COLOR_DPS_YELLOW, 255);
        surf->DrawLine(stX, stY - 6, stX - 6, stY + 6);
        surf->DrawLine(stX - 6, stY + 6, stX + 6, stY + 6);
        surf->DrawLine(stX + 6, stY + 6, stX, stY - 6);
    }

    surf->YellowFont();
    if (DPS::Instance()->GetCompool()->Read<bool>(PC_LT_50))
        surf->DrawTextFlash(23, 10, "Pc < 50");
    // surf->DrawTextFlash(20, 4, "SRB SEP INH");
    // surf->DrawTextFlash(21, 6, "ET SEP INH");
    // surf->DrawTextFlash(21, 8, "ET SEP MAN");
}

const char *AscentTrajectory::GetTitle()
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

bool AscentTrajectory::CanTransition(int newMM)
{
    return newMM == 103 || newMM == 0;
}
