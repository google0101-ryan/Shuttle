#include <dps/MemoryConfig.h>

MemoryConfig mc1 =
{
    .num = 1,
    .gnc = true,
    .index = 1,
    .targetMask = 0b1111,
    .nbat =
    {
        .string = {1, 2, 3, 4},
        .pl = 0,
        .crt = {1, 2, 3, 4},
        .launch = {1, 2},
        .mm = {1, 2}
    },
    .supportedOps = {1, 6}
};

MemoryConfig mc2 =
{
    .num = 2,
    .gnc = true,
    .index = 2,
    .targetMask = 0b111,
    .nbat =
    {
        .string = {1, 2, 3, 1},
        .pl = 0,
        .crt = {1, 2, 3, 2},
        .launch = {0, 0},
        .mm = {1, 2}
    },
    .supportedOps = {2, -1}
};

MemoryConfig mcTable[] =
{
    mc1,
    mc2
};

MemoryConfig &GetConfig(int mc)
{
    return mcTable[mc];
}

void SetConfig(int mc, MemoryConfig &conf)
{
    mcTable[mc] = conf;
}
