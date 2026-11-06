#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <functional>

class Button
{
public:
    void Init(SDL_Renderer* parent, int x, int y, const char* texFile);

    void SetOnClicked(std::function<void(SDL_Event&, void*)> clicked) { this->clicked = clicked; }

    void Draw(SDL_Renderer* parent);
    void OnMouseDown(SDL_Event& e, void* ctxt);
private:
    int x, y, w, h;
    SDL_Surface* texSurf;
    SDL_Texture* tex;
    std::function<void(SDL_Event&, void*)> clicked;
};