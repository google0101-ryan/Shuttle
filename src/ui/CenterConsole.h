#pragma once

#include <vector>
#include <ui/Switch.h>

class CenterConsole
{
public:
    void Init();

    void Draw();
    void MouseEvent(SDL_Event& e);
private:
    void AddSwitch(int x, int y, Switch::OnClicked_t handler);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Switch> switches;
};