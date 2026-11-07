#include "CenterConsole.h"
#include <dps/DPS.h>

void OnBFSEnable(int state, SDL_Event &e, void *ctxt)
{
    DPS::Instance()->SetBFSEnable(state == SWITCH_ON ? true : false);
}

void SwitchLeftKB(int state, SDL_Event& e, void* ctxt)
{
    if (state == SWITCH_ON)
        DPS::Instance()->SetKB1(false);
    else
        DPS::Instance()->SetKB1(true);
}

void SwitchRightKB(int state, SDL_Event& e, void* ctxt)
{
    if (state == SWITCH_OFF)
        DPS::Instance()->SetKB2(false);
    else
        DPS::Instance()->SetKB2(true);
}

void CenterConsole::Init()
{
    window = SDL_CreateWindow("Center Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 840, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    AddSwitch(270, 180, SwitchLeftKB, 270, SWITCH_ON);
    AddSwitch(480, 180, SwitchRightKB, 270);
    AddSwitch(180, 315, OnBFSEnable);
}

void CenterConsole::Draw()
{
    SDL_SetRenderDrawColor(renderer, 95, 102, 114, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int i = 0; i < switches.size(); i++)
        switches[i].Draw(renderer);

    SDL_RenderPresent(renderer);
}

void CenterConsole::MouseEvent(SDL_Event &e)
{
    SDL_Window* evtWindow = SDL_GetWindowFromID(e.button.windowID);

    if (evtWindow != window)
        return;

    for (int i = 0; i < switches.size(); i++)
        switches[i].OnMouseDown(e, (void*)this);
}

void CenterConsole::AddSwitch(int x, int y, Switch::OnClicked_t handler, int rot, int defaultState)
{
    Switch s;
    s.Init(renderer, x, y);
    s.SetOnClicked(handler);
    s.Rotate(rot);
    s.SetState(defaultState);

    switches.push_back(s);
}
