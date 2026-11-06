#pragma once

#include <vector>
#include <Page.h>

class InputParser
{
public:
    // Parse an ITEM command
    static std::vector<Item> ParseItem(char* input);
private:
    static void SkipWhitespace(char*& ptr);
};