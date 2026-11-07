#include "Switch.h"

#include <cassert>

void Switch::Init(SDL_Renderer *parent, int x, int y, SwitchType type)
{
    this->type = type;
    this->x = x;
    this->y = y;
    
    onStateSurf = IMG_Load("res/switch_on.png");
    offStateSurf = IMG_Load("res/switch_off.png");

    if (type == THREE_WAY)
    {
        assert(0);
    }

    onState = SDL_CreateTextureFromSurface(parent, onStateSurf);
    offState = SDL_CreateTextureFromSurface(parent, offStateSurf);

    w = onStateSurf->w;
    h = onStateSurf->h;

    state = SWITCH_OFF;
}

void Switch::Rotate(int r)
{
    rot = r;
}

void Switch::Draw(SDL_Renderer *parent)
{
    SDL_Texture* targ;

    switch (state)
    {
    case SWITCH_OFF:
        targ = offState;
        break;
    case SWITCH_ON:
        targ = onState;
        break;
    default:
        assert(0);
    }

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopyEx(parent, targ, NULL, &dst, rot, NULL, SDL_FLIP_NONE);
}

void Switch::OnMouseDown(SDL_Event &e, void* ctxt)
{
    if (e.button.button != SDL_BUTTON_LEFT && e.button.button != SDL_BUTTON_RIGHT)
        return;

    if (e.button.x < x || e.button.x > x+w)
        return;

    if (e.button.y < y || e.button.y > y+h)
        return;

    int oldState = state;

    if (e.button.button == SDL_BUTTON_LEFT)
    {
        // Advance switch state
        if (state != SWITCH_ON)
        {
            state++;
            if (type == TWO_WAY && state == SWITCH_MID)
                state++;
        }
    }
    else
    {
        if (state != SWITCH_OFF)
        {
            state--;
            if (type == TWO_WAY && state == SWITCH_MID)
                state--;
        }
    }

    if (handler && oldState != state)
        handler(state, e, ctxt);
}

void Switch::SetOnClicked(OnClicked_t handler)
{
    this->handler = handler;
}
