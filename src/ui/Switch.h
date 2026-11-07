#pragma once

#include <SDL2/SDL_image.h>
#include <functional>

enum SwitchType
{
    TWO_WAY,
    THREE_WAY
};

enum SwitchState
{
    SWITCH_OFF,
    SWITCH_MID,
    SWITCH_ON
};

class Switch
{
public:
    using OnClicked_t = std::function<void(int, SDL_Event&, void*)>;
public:
    void Init(SDL_Renderer* parent, int x, int y, SwitchType type = TWO_WAY);
    void Rotate(int r);
    void SetState(int state) { this->state = state; }

    void Draw(SDL_Renderer* parent);

    void OnMouseDown(SDL_Event& e, void* ctxt);
    void SetOnClicked(OnClicked_t handler);
private:
    int state = SWITCH_OFF;
    SDL_Surface* onStateSurf, *midStateSurf, *offStateSurf;
    SDL_Texture* onState, *midState, *offState;
    OnClicked_t handler;
    int x, y, w, h;
    SwitchType type;
    int rot = 0;
};