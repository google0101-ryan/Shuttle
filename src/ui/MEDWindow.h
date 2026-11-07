#pragma once

#include <SDL2/SDL.h>
#include <SDL_FontCache.h>

class IDP;

#define COLOR_DPS_NORMAL 128, 255, 0
#define COLOR_DPS_YELLOW 255, 255, 0
#define COLOR_ERROR_NORMAL 255, 0, 0
#define COLOR_MEDS_NORMAL 0, 255, 255

class MEDWindow
{
public:
    void Init(IDP* idp, int w = 512, int h = 512);
    SDL_Window* GetWindow() { return window; }

    void Clear();
    void Tick();
    void Present();
    void DPSFont();
    void MEDSFont();
    void ErrorFont();
    void YellowFont();
    void SetDrawColor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);
    void DrawTextRaw(double x, double y, const char* text, ...);
    void DrawText(double x, double y, const char* text, ...);
    void DrawTextFlash(double x, double y, const char* text, ...);
    void DrawTextUnderline(double x, double y, const char* text, ...);
    void DrawLine(double x1, double y1, double x2, double y2);
    void DrawBox(double x1, double y1, double x2, double y2);
    void DrawRectangle(double x1, double y1, double x2, double y2);

    void PlaySound(int duration, const char* fileName);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    FC_Font* dpsFont;
    FC_Font* medsFont;
    FC_Font* errorFont;
    FC_Font* yellowFont;
    FC_Font* font;
    bool flash;
    int lastFlashTime;

    int scalex, scaley;
};