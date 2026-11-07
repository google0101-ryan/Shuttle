#include <ui/MEDWindow.h>
#include <ui/Keyboard.h>
#include <ui/CenterConsole.h>
#include <dps/DPS.h>

#define NUM_CRTS 3

int main(int argc, char** argv)
{
    MEDWindow  windows[NUM_CRTS];
    for (int i = 0; i < NUM_CRTS; i++)
    {
        windows[i].Init(nullptr, 522);
    }

    SDL_Rect disp;
    SDL_GetDisplayBounds(0, &disp);

    SDL_SetWindowPosition(windows[0].GetWindow(), 0, 0);
    SDL_SetWindowPosition(windows[1].GetWindow(), disp.w - 522, 0);
    SDL_SetWindowPosition(windows[2].GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    Keyboard cdr, plt;
    cdr.Init(0);
    plt.Init(1);

    SDL_SetWindowPosition(cdr.GetWindow(), (522 / 2) - 120, 512);
    SDL_SetWindowPosition(plt.GetWindow(), (((disp.w - 522) + disp.w) / 2) - 120, 512);

    CenterConsole console;
    console.Init();

    SDL_SetWindowPosition(console.GetWindow(), SDL_WINDOWPOS_CENTERED, (disp.h / 2) + 256);

    DPS dps;
    dps.Init();

    while (true)
    {
        dps.Tick();

        for (int i = 0; i < NUM_CRTS; i++)
            windows[i].Tick();

        for (int i = 0; i < NUM_CRTS; i++)
        {
            dps.Draw(i, &windows[i]);
        }

        cdr.Draw();
        plt.Draw();
        console.Draw();

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                exit(1);
            case SDL_WINDOWEVENT:
                switch (e.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    exit(1);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                cdr.MouseEvent(e);
                plt.MouseEvent(e);
                console.MouseEvent(e);
                break;
            default:
                break;
            }
        }

        for (int i = 0; i < NUM_CRTS; i++)
            windows[i].Present();
    }
}