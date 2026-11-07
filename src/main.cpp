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

    Keyboard cdr, plt;
    cdr.Init(0);
    plt.Init(1);

    CenterConsole console;
    console.Init();

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