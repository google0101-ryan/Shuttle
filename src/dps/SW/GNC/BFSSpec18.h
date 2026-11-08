#pragma once

#include <dps/SW/Page.h>

class BFSSysSumm1 : public Page
{
public:
    virtual void Draw(MEDWindow* surf);
    virtual int GetNum() { return 18; }
    virtual const char* GetTitle() { return "GNC SYS SUMM 1"; }
};