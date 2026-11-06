#pragma once

#include <vector>

struct NBAT
{
    int string[4];
    int pl;
    int crt[4];
    int launch[2];
    int mm[2];
};

struct MemoryConfig
{
    int num;
    bool gnc;
    int index; // This is different from num, num is used for ITEM 1, while index is the index within the major function (i.e. this can be 2 for GNC OPS 2 or 2 for SM OPS 2)
    int targetMask;
    NBAT nbat;
    int supportedOps[2];
};

extern MemoryConfig mc1;

MemoryConfig& GetConfig(int mc);
void SetConfig(int mc, MemoryConfig& conf);