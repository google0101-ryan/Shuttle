#pragma once

#include <stdint.h>

#define COMPOOL_SIZE 0x10000

// Compool variables
#define K_CMD 0x1948
#define DISPLAYTITLE_ID 0x3910

// Contains global variables available for the DPS to read/write, like K_CMD
class Compool
{
public:
    template<typename T>
    void Write(int index, T data)
    {
        (*(T*)&compool[index]) = data;
    }

    template<typename T>
    T Read(int index)
    {
        return (*(T*)&compool[index]);
    }
private:
    uint64_t compool[COMPOOL_SIZE] = {0};
};