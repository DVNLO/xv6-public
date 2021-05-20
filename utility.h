#ifndef UTILITY_H
#define UTILITY_H

#include "user.h"

#define false 0
#define true 1

/// @brief prints an integer val to terminal
void
print_int(int const val)
{
    printf(1, "%d\n", val);
}

/// @brief returns true if the provided character val is a
/// whitespace character. Otherwise, returns false.
int
is_whitespace(char const val)
{
    switch(val)
    {
        case ' ':
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
            return true;
        default:
            return false;
    }
}

/// @brief return a non-negative integer value converted
/// from the provided c-string. Assumes the provided string
/// contains a continuous run of digits potentially preceeded
/// by whitespace.
int
to_int(char const * const str)
{
    int ret = 0;
    if(!str)
        return ret;
    int i = 0;
    // advance over whitespace
    while(str[i] && is_whitespace(str[i]))
    {
        ++i;
    }
    // iteratively construct ret from str digits
    while(str[i])
    {
        ret *= 10;
        ret += (int)(str[i] - '0');
        ++i;
    }
    return ret;
}

#endif // UTILITY_H
