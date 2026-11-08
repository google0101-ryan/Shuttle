#include "IDP.h"
#include <dps/GPC.h>

#include <string>
#include <vector>
#include "DPS.h"

bool IsDigit(int key)
{
    return (key >= KEY_0) && (key <= KEY_9);
}

const char* ScratchpadString(int* buf, int len)
{
    static char dst[100] = {0};
    memset(dst, 0, sizeof(dst));

    int j = 0;
    for (int i = 0; i < len; i++)
    {
        switch (buf[i])
        {
        case KEY_ITEM:
            strcat(dst, "ITEM ");
            break;
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
            strcat(dst, std::to_string(buf[i]).c_str());
            break;
        case KEY_MINUS:
            strcat(dst, "-");
            break;
        case KEY_PLUS:
            strcat(dst, "+");
            break;
        case KEY_EXEC:
            strcat(dst, " EXEC");
            break;
        case KEY_PRO:
            strcat(dst, " PRO");
            break;
        case KEY_OPS:
            strcat(dst, "OPS ");
            break;
        case KEY_SPEC:
            strcat(dst, "SPEC ");
            break;
        case KEY_RESUME:
            strcat(dst, "RESUME ");
            break;
        case KEY_GPC_CRT:
            strcat(dst, "GPC/CRT ");
            break;
        }
    }

    return dst;
}

void DrawScratchpad(char* dst, int* buf, int len)
{
    int j = 0;
    bool firstSign = false;
    int item = 0;

    const char* str = ScratchpadString(buf, len);
    len = strlen(str);

    for (int i = 0; i <= len; i++)
    {
        if ((str[i] == '+') || (str[i] == '-'))
        {
            if (!firstSign)
            {
                firstSign = true;

                if (dst[j-1] >= '0' && dst[j-1] <= '9')
                {
                    if (dst[j-2] >= '0' && dst[j-2] <= '9')
                    {
                        item = (dst[j-1] - '0') + ((dst[j-2] - '0') * 10);

                        sprintf(dst + j - 2, "(%d)", item);
                        j += 2;
                    }
                    else
                    {
                        item = dst[j-1] - '0';

                        sprintf(dst + j - 1, "(0%d)", item);
                        j += 3;
                    }
                }
            }
            else
            {
                if (str[i-1] == '+' || str[i-1] == '-')
                {
                    item++;
                    sprintf(dst + j - 4, "%02d)", item);
                    j -= 1;
                }
                else
                {
                    item++;
                    sprintf( dst + j, " (%02d)", item);
                    j += 5;
                }
            }
        }
        
        dst[j++] = str[i];
    }

    dst[j] = 0;
}

void IDP::Init(int id)
{
    this->id = id;

    inputError = false;
    inputLineLen = 0;
}

void IDP::Tick()
{
    if (gpc)
        gpc->Tick();
    
    if (!lineComplete || processed)
        return;

    switch (inputLine[0])
    {
    case KEY_OPS:
        ParseOpsCommand();
        break;
    case KEY_SPEC:
        ParseSpecCommand();
        break;
    case KEY_ITEM:
        ParseItemCommand();
        break;
    case KEY_RESUME:
        processed = true;
        gpc->GoToSpec(-1);
        break;
    case KEY_GPC_CRT:
        ParseGpcCrtCommand();
        break;
    default:
        inputError = true;
        processed = true;
        break;
    }
}

void DrawButton(int x, MEDWindow* surf)
{
    surf->DrawLine(x - 36, 510, x - 36, 483);
    surf->DrawLine(x - 36, 484, x + 36, 484);
    surf->DrawLine(x + 36, 483, x + 36, 510);
}

void IDP::Draw(MEDWindow *surf)
{
    surf->DPSFont();
    if (gpc)
    {
        surf->Clear();
        gpc->GetCurPage()->Draw(surf);

        // IDP 
        surf->SetDrawColor(COLOR_DPS_NORMAL);
        surf->DPSFont();
        surf->DrawTextRaw(247, 423, "%d", id);
        // box around identifier
        surf->DrawBox(231, 415, 271, 453);

        // Draw scratchpad
        char buf[1024] = { 0 };
        DrawScratchpad(buf, inputLine, inputLineLen);

        int flashingEntry = GetFlashingEntry();
        if (flashingEntry != 0)
        {
            char str2[16] = { 0 };
            strncpy(str2, buf, flashingEntry);
            surf->DrawTextFlash(1, 26, str2);
        }

        surf->DrawText(1 + flashingEntry, 26, buf + flashingEntry);

        // Draw error messages
        if (inputError)
        {
            surf->ErrorFont();
            surf->DrawTextFlash(1, 25, "ILLEGAL ENTRY");
        }
        else if (errorMsgQ.size() > 0 && errorMsgQ.front().size() != 0)
        {
            surf->ErrorFont();
            surf->DrawTextFlash(1, 25, errorMsgQ.front().c_str());
        }
    }
    else
    {
        // Draw large red x
        surf->SetDrawColor(COLOR_ERROR_NORMAL, 255);
        surf->DrawLine(0, 0, 512, 364);
        surf->DrawLine(512, 0, 0, 364);
    }
}

void IDP::DrawKB1Ind(MEDWindow* surf)
{
    surf->SetDrawColor(COLOR_ERROR_NORMAL, 255);
    surf->DrawRectangle(110, 438, 231, 443);
}

void IDP::DrawKB2Ind(MEDWindow* surf)
{
    surf->SetDrawColor(COLOR_DPS_YELLOW, 255);
    surf->DrawRectangle(272, 438, 402, 443);
}

void IDP::SetGPC(GPC *gpc)
{
    this->gpc = gpc;
    if (gpc)
        gpc->SetParent(this);
}

GPC *IDP::GetGPC()
{
    return gpc;
}

void IDP::SendKey(int key)
{
    if (!gpc)
        return; // Don't do keyboard processing if there's no assigned GPC

    if (inputLineLen >= 100)
    {
        inputError = true;
        return;
    }

    // Special keys
    switch (key)
    {
    case KEY_CLEAR:
        if (inputLineLen > 0)
        {
            inputLineLen--;
            inputLine[inputLineLen] = 0;
        }
        return;
    case KEY_MSG_RESET:
        if (inputLineLen > 0 && !processed)
        {
            inputError = true;
            return;
        }
        inputError = false;
        if (errorMsgQ.size() > 0)
            errorMsgQ.pop();
        lineComplete = true;
        return;
    }

    // If the last key was PRO, EXEC, SYS SUMM, FAULT SUMM, or MSG RESET then clear the scratchpad next time a key is pressed
    if (lineComplete)
    {
        inputLineLen = 0;
        lineComplete = false;
        processed = false;
        memset(inputLine, 0, sizeof(inputLine));
    }
    
    inputLine[inputLineLen++] = key;
    
    switch (key)
    {
    case KEY_EXEC:
    case KEY_PRO:
    case KEY_MSG_RESET:
    case KEY_SYS_SUMM:
    case KEY_FAULT_SUMM:
    case KEY_RESUME:
        lineComplete = true;
        break;
    }

    printf("%d\n", inputLineLen);
}

void IDP::ParseItemCommand()
{
    // lineComplete = false;
    processed = true;
    // inputLineLen = 0;

    if (!IsDigit(inputLine[1]))
    {
        inputError = true;
        return;
    }

    std::vector<ItemCommand> items;
    items.reserve(10);

    // Parse out first item number
    int item = 0;
    int j = 1;

    while (inputLine[j] >= KEY_0 && inputLine[j] <= KEY_9)
    {
        item *= 10;
        item += inputLine[j];
        j++;
    }

    printf("Executing item %d\n", item);

    while (inputLine[j] != KEY_EXEC)
    {
        if (inputLine[j] != KEY_MINUS && inputLine[j] != KEY_PLUS)
        {
            inputError = true;
            return;
        }

        bool neg = inputLine[j] == KEY_MINUS;
        j++;

        ItemCommand cmd = {0};
        cmd.item = item++;
        while (inputLine[j] != KEY_MINUS && inputLine[j] != KEY_PLUS && inputLine[j] != KEY_EXEC)
        {
            cmd.val *= 10;
            cmd.val += inputLine[j];
            j++;
        }

        printf("%d->%d\n", cmd.val, cmd.item);

        items.push_back(cmd);
    }

    // No following + or -
    if (items.size() == 0)
    {
        items.push_back(ItemCommand{.item = item, .val = -1});
    }

    // Send commands to GPC
    for (int i = 0; i < items.size(); i++)
    {
        if (!gpc->GetCurPage()->ExecuteItem(items[i]))
            inputError = true;
    }
}

void IDP::ParseOpsCommand()
{
    // lineComplete = false;
    // inputLineLen = 0;
    processed = true;

    if (!IsDigit(inputLine[1]))
    {
        inputError = true;
        return;
    }

    int* ptr = &inputLine[1];
    int mm = 0;
    while (IsDigit(*ptr))
    {
        mm *= 10;
        mm += *ptr;
        ptr++;
    }

    if (*ptr != KEY_PRO)
    {
        inputError = true;
        return;
    }

    gpc->PreOpsCommand();

    auto mc = gpc->GetMC();
    for (int i = 0; i < 5; i++)
    {
        if (mc.targetMask & (1<<i))
        {
            if (!DPS::Instance()->GetGPC(i)->OpsCommand(mm))
            {
                if (DPS::Instance()->GetGPC(i)->GetParent())
                {
                    DPS::Instance()->GetGPC(i)->GetParent()->inputError = true;
                }
                continue;
            }
        }
    }

    if (!DPS::Instance()->GetGPC(4)->OpsCommand(mm))
    {
        if (DPS::Instance()->GetGPC(4)->GetParent())
            DPS::Instance()->GetGPC(4)->GetParent()->inputError = true;
    }
}

void IDP::ParseSpecCommand()
{
    //lineComplete = false;
    // inputLineLen = 0;
    processed = true;

    if (!IsDigit(inputLine[1]))
    {
        inputError = true;
        return;
    }

    int* ptr = &inputLine[1];
    int spec = 0;
    while (IsDigit(*ptr))
    {
        spec *= 10;
        spec += *ptr;
        ptr++;
    }

    if (*ptr != KEY_PRO)
    {
        inputError = true;
        return;
    }

    if (!gpc->GoToSpec(spec))
        inputError = true;
}

void IDP::ParseGpcCrtCommand()
{
    processed = true;

    if (!IsDigit(inputLine[1]) || !IsDigit(inputLine[2]) || inputLine[3] != KEY_EXEC)
    {
        inputError = true;
        return;
    }

    if (inputLine[1] < 0 || inputLine[1] > 5)
    {
        inputError = true;
        return;
    }

    GPC* gpc;
    if (inputLine[1] != 0)
        gpc = DPS::Instance()->GetGPC(inputLine[1] - 1);
    else
        gpc = nullptr;

    if (inputLine[2] < 1 || inputLine[2] > 4)
    {
        inputError = true;
        return;
    }

    IDP* idp = DPS::Instance()->GetIDP(inputLine[2] - 1);

    idp->SetGPC(gpc);
}

int IDP::GetFlashingEntry()
{
    if (processed || lineComplete)
        return 0;

    switch (inputLine[0])
    {
    case KEY_OPS:
        return 3;
    case KEY_SPEC:
    case KEY_ITEM:
        return 4;
    case KEY_GPC_CRT:
        return 7;
    case KEY_IO_RESET:
        return 9;
    default:
        return 0;
    }
}

void IDP::AddError(GPC *gpc, const char *msg, const char *msg2)
{
    char errorMsg[1024];
    int padMsg = 10 - strlen(msg);
    int padLeftMsg = padMsg / 2;
    int padRightMsg = padMsg - padLeftMsg;

    int padMsg2 = 4 - strlen(msg);
    int padLeftMsg2 = padMsg2 / 2;
    int padRightMsg2 = padMsg2 - padLeftMsg2;
    
    int len = sprintf(errorMsg, "    %*s%s%*s %*s%s%*s        %d        %s", padLeftMsg, "", msg, padRightMsg, "", padLeftMsg2, "", msg2, padRightMsg2, "", gpc->GetID(), gpc->GetTime()->GetTimeString() + 4);
    if (errorMsgQ.size() != 0)
        sprintf(errorMsg+len, "(%02d)", errorMsgQ.size());

    errorMsgQ.push(errorMsg);
}
