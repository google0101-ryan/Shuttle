#include "CenterConsole.h"
#include <dps/DPS.h>

void OnBFSEnable(int state, SDL_Event &e, void *ctxt)
{
    DPS::Instance()->SetBFSEnable(state == SWITCH_ON ? true : false);
}

void CenterConsole::Init()
{
    window = SDL_CreateWindow("Center Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 420, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    AddSwitch(180, 30, OnBFSEnable);
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

void CenterConsole::AddSwitch(int x, int y, Switch::OnClicked_t handler)
{
    Switch s;
    s.Init(renderer, x, y);
    s.SetOnClicked(handler);

    switches.push_back(s);
}
