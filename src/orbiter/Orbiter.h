#pragma once

#include <dps/DPS.h>
#include <ui/Keyboard.h>
#include <ui/MEDWindow.h>
#include <ui/CenterConsole.h>

// The main Space Shuttle class, this is the actual Spaceplane part
class Orbiter
{
public:
    Orbiter();
private:
    DPS dps;

    // TODO: We need to seriously refactor the UI stuff
    // Basically, we need to seperate logic from UI, so that way if I ever decide to take this thing 3D, I can rework most of the switch logic
};