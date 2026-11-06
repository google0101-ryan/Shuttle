#include "Parser.h"

#include <stdio.h>
#include <ctype.h>
#include <cstdlib>

std::vector<Item> InputParser::ParseItem(char *input)
{
    std::vector<Item> items;

    if (*input != 'i')
    {
        printf("Not an ITEM command!\n");
        return items;
    }

    input++;
    SkipWhitespace(input);

    // Read first item number
    int baseItem = 0;
    while (*input != '+' && *input != '-' && *input != 'e')
    {
        if (!isdigit(*input))
        {
            printf("Invalid character in item number\n");
            exit(1);
        }

        baseItem *= 10;
        baseItem += *input - '0';
        input++;
    }

    bool neg = *input == '-';
    input++;

    int num = 0;
    while (*input >= ' ' && *input != 'e')
    {
        while (*input >= ' ' && *input != '+' && *input != '-'
                && *input != 'e')
        {
            num *= 10;
            num += *input - '0';
            input++;
        }

        if (neg)
            num = -num;

        Item item;
        item.num = baseItem + items.size();
        item.val = num;

        items.push_back(item);

        if (*input == '+' || *input == '-')
        {
            num = 0;
            neg = *input == '-';
            input++;
        }
    }

    return items;
}

void InputParser::SkipWhitespace(char *&ptr)
{
    while (*ptr <= ' ')
    {
        ptr++;
    }
}
