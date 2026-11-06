#include "Button.h"

void Button::Init(SDL_Renderer* renderer, int x, int y, const char *texFile)
{
    this->x = x;
    this->y = y;

    texSurf = IMG_Load(texFile);
    tex = SDL_CreateTextureFromSurface(renderer, texSurf);

    w = texSurf->w;
    h = texSurf->h;
}

void Button::Draw(SDL_Renderer *parent)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(parent, tex, NULL, &dst);
}

void Button::OnMouseDown(SDL_Event &e, void* ctxt)
{
    if (e.button.button != SDL_BUTTON_LEFT)
        return;

    if (e.button.x < x || e.button.x > x+w)
        return;

    if (e.button.y < y || e.button.y > y+h)
        return;

    // We were cliked!
    if (clicked)
        clicked(e, ctxt);
}
