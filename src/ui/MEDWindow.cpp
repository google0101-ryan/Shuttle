#include <ui/MEDWindow.h>

static bool sdlInitialized = false;

void MEDWindow::Init(IDP *idp, int w, int h)
{
    if (!sdlInitialized)
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            printf("Failed to init SDL3: %s\n", SDL_GetError());
            exit(1);
        }

        if (TTF_Init() == -1)
        {
            printf("Failed to init TTF fonts: %s\n", TTF_GetError());
            exit(1);
        }
    }

    window = SDL_CreateWindow("MEDS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    
    if (!window)
    {
        printf("Failed to create MEDS window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    
    if (!window)
    {
        printf("Failed to create MEDS renderer: %s\n", SDL_GetError());
        exit(1);
    }
    
    dpsFont = FC_CreateFont();
    FC_LoadFont(dpsFont, renderer, "res/SSV_Font_A.otf", 10, FC_MakeColor(128, 255, 0, 255), TTF_STYLE_NORMAL);

    medsFont = FC_CreateFont();
    FC_LoadFont(medsFont, renderer, "res/SSV_Font_A.otf", 9, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_NORMAL);

    errorFont = FC_CreateFont();
    FC_LoadFont(errorFont, renderer, "res/SSV_Font_A.otf", 10, FC_MakeColor(255, 0, 0, 255), TTF_STYLE_NORMAL);

    yellowFont = FC_CreateFont();
    FC_LoadFont(yellowFont, renderer, "res/SSV_Font_A.otf", 10, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_NORMAL);

    font = dpsFont;
}

void MEDWindow::Clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 1, 0x20, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void MEDWindow::Tick()
{
    double seconds = ((double)SDL_GetTicks() / 1000);
    int t = (int)(seconds * 2);

    flash = (t % 2) == 1;
}

void MEDWindow::Present()
{
    SDL_RenderPresent(renderer);
}

void MEDWindow::DPSFont()
{
    font = dpsFont;
}

void MEDWindow::MEDSFont()
{
    font = medsFont;
}

void MEDWindow::ErrorFont()
{
    font = errorFont;
}

void MEDWindow::YellowFont()
{
    font = yellowFont;
}

void MEDWindow::SetDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void MEDWindow::DrawTextRaw(double x, double y, const char *text, ...)
{
    static char buf[4096];

    memset(buf, 0, 4096);
    va_list ap;
    va_start(ap, text);
    vsprintf(buf, text, ap);
    va_end(ap);

    // offset y slightly to avoid hugging the top of the screen
    y += 5;

    FC_Draw(font, renderer, x, y, buf);
}

void MEDWindow::DrawText(double x, double y, const char *text, ...)
{
    static char buf[4096];

    memset(buf, 0, 4096);
    va_list ap;
    va_start(ap, text);
    vsprintf(buf, text, ap);
    va_end(ap);
    int line = y;

    // x and y are in characters
    x *= 10;
    y *= 14;

    // offset y slightly to avoid hugging the top of the screen
    y += 5;

    FC_Draw(font, renderer, x, y, buf);
}

void MEDWindow::DrawTextFlash(double x, double y, const char *text, ...)
{
    static char buf[4096];

    if (!flash)
        return;

    memset(buf, 0, 4096);
    va_list ap;
    va_start(ap, text);
    vsprintf(buf, text, ap);
    va_end(ap);
    int line = y;

    // x and y are in characters
    x *= 10;
    y *= 14;

    // offset y slightly to avoid hugging the top of the screen
    y += 5;

    FC_Draw(font, renderer, x, y, buf);
}

void MEDWindow::DrawTextUnderline(double x, double y, const char *text, ...)
{
    static char buf[4096];

    memset(buf, 0, 4096);
    va_list ap;
    va_start(ap, text);
    vsprintf(buf, text, ap);
    va_end(ap);
    int line = y;

    // x and y are in characters
    x *= 10;
    y *= 14;

    // offset y slightly to avoid hugging the top of the screen
    y += 5;

    FC_Draw(font, renderer, x, y, buf);
    
    // Draw the underline
    for (int i = 0; i < strlen(buf); i++)
    {
        SDL_SetRenderDrawColor(renderer, 128, 255, 0, SDL_ALPHA_OPAQUE);
        DrawLine(x+1, y+11, x+8, y+11);
        x += 10;
    }
}

void MEDWindow::DrawLine(double x1, double y1, double x2, double y2)
{
    // SDL_SetRenderDrawColor(renderer, COLOR_DPS_NORMAL, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void MEDWindow::DrawBox(double x1, double y1, double x2, double y2)
{
    SDL_Rect rect;
    rect.x = std::min(x1, x2);
    rect.y = std::min(y1, y2);
    rect.w = (x1 > x2) ? x1-x2 : x2-x1;
    rect.h = (y1 > y2) ? y1-y2 : y2-y1;

    SDL_RenderDrawRect(renderer, &rect);
}

void MEDWindow::PlaySound(int duration, const char *fileName)
{
}
