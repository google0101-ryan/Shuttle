#pragma once

#include <SDL2/SDL.h>
#include <ui/Button.h>

enum Keys
{
    KEY_0 = 0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_PLUS,
    KEY_MINUS,
    KEY_ITEM,
    KEY_EXEC,
    KEY_OPS,
    KEY_PRO,
    KEY_CLEAR,
    KEY_DOT,
    KEY_SPEC,
    KEY_IO_RESET,
    KEY_MSG_RESET,
    KEY_FAULT_SUMM,
    KEY_SYS_SUMM,
    KEY_GPC_CRT,
    KEY_ACK,
    KEY_RESUME,
};

class Keyboard
{
public:
    void Init(int id);

    void Draw();
    void MouseEvent(SDL_Event& e);

    void AddInput(int button);
private:
    int id;

    SDL_Window* window;
    SDL_Renderer* renderer;
    Button* item;
    Button* num[10];
    Button* plus, *minus;
    Button* exec;
    Button* clear;
    Button* msgReset;
    Button* ops;
    Button* pro;
    Button* spec;
    Button* resume;
    Button* gpccrt;

    int inputBuf[1024];
    int inputIdx;
};