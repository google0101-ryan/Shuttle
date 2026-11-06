#pragma once

#include <ui/MEDWindow.h>
#include <dps/IDP.h>

class GPC;

class Page
{
public:
    virtual ~Page() = default;

    virtual void Tick() {}

    void SetParent(GPC* parent) { this->parent = parent; }

    virtual void Draw(MEDWindow* surf) = 0;
    virtual int GetNum() = 0;
    virtual const char* GetTitle() = 0;
    virtual bool CanTransition(int newMM) { return false; }

    virtual bool ExecuteItem(ItemCommand& cmd) { return false; }
protected:
    GPC* parent;
};