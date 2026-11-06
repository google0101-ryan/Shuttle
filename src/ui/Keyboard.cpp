#include "Keyboard.h"
#include <dps/DPS.h>

template<int key>
void SendKey(SDL_Event&, void* ctxt)
{
    Keyboard* kb = (Keyboard*)ctxt;

    kb->AddInput(key);
}

void Keyboard::Init(int id)
{
    this->id = id;

    const char* names[] =
    {
        "CDR",
        "PLT",
        "REAR"
    };

    char windowName[30];
    sprintf(windowName, "%s KEYBOARD", names[id]);
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 240, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    item = new Button();
    item->Init(renderer, 0, 180, "res/item.png");
    item->SetOnClicked(SendKey<KEY_ITEM>);

    for (int i = 1; i < 10; i++)
    {
        char name[20];
        sprintf(name, "res/%d.png", i);
        
        num[i] = new Button();
        num[i]->Init(renderer, (((i-1) % 3)*60)+60, ((i-1) / 3)*60 + 180, name);
    }

    num[0] = new Button();
    num[0]->Init(renderer, 120, 360, "res/0.png");

    num[0]->SetOnClicked(SendKey<KEY_0>);
    num[1]->SetOnClicked(SendKey<KEY_1>);
    num[2]->SetOnClicked(SendKey<KEY_2>);
    num[3]->SetOnClicked(SendKey<KEY_3>);
    num[4]->SetOnClicked(SendKey<KEY_4>);
    num[5]->SetOnClicked(SendKey<KEY_5>);
    num[6]->SetOnClicked(SendKey<KEY_6>);
    num[7]->SetOnClicked(SendKey<KEY_7>);
    num[8]->SetOnClicked(SendKey<KEY_8>);
    num[9]->SetOnClicked(SendKey<KEY_9>);

    plus = new Button();
    plus->Init(renderer, 180, 360, "res/plus.png");
    plus->SetOnClicked(SendKey<KEY_PLUS>);

    minus = new Button();
    minus->Init(renderer, 60, 360, "res/minus.png");
    minus->SetOnClicked(SendKey<KEY_MINUS>);

    exec = new Button();
    exec->Init(renderer, 0, 240, "res/exec.png");
    exec->SetOnClicked(SendKey<KEY_EXEC>);

    clear = new Button();
    clear->Init(renderer, 60, 420, "res/clear.png");
    clear->SetOnClicked(SendKey<KEY_CLEAR>);

    msgReset = new Button();
    msgReset->Init(renderer, 120, 0, "res/msg.png");
    msgReset->SetOnClicked(SendKey<KEY_MSG_RESET>);

    ops = new Button();
    ops->Init(renderer, 0, 300, "res/ops.png");
    ops->SetOnClicked(SendKey<KEY_OPS>);

    pro = new Button();
    pro->Init(renderer, 180, 420, "res/pro.png");
    pro->SetOnClicked(SendKey<KEY_PRO>);

    inputIdx = 0;
}

void Keyboard::Draw()
{
    item->Draw(renderer);

    for (int i = 0; i < 10; i++)
    {
        num[i]->Draw(renderer);
    }

    minus->Draw(renderer);
    plus->Draw(renderer);
    exec->Draw(renderer);
    clear->Draw(renderer);
    msgReset->Draw(renderer);
    ops->Draw(renderer);
    pro->Draw(renderer);

    SDL_RenderPresent(renderer);
}

void Keyboard::MouseEvent(SDL_Event &e)
{
    SDL_Window* evtWindow = SDL_GetWindowFromID(e.button.windowID);

    if (evtWindow != window)
        return;

    item->OnMouseDown(e, (void*)this);
    for (int i = 0; i < 10; i++)
        num[i]->OnMouseDown(e, (void*)this);
    minus->OnMouseDown(e, (void*)this);
    plus->OnMouseDown(e, (void*)this);
    exec->OnMouseDown(e, (void*)this);
    clear->OnMouseDown(e, (void*)this);
    msgReset->OnMouseDown(e, (void*)this);
    ops->OnMouseDown(e, (void*)this);
    pro->OnMouseDown(e, (void*)this);
}

void Keyboard::AddInput(int button)
{
    DPS::Instance()->SendKey(id, button);
}
