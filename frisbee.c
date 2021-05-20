#include "types.h"
#include "stat.h"
#include "user.h"

/// @brief prints frisbee usage to terminal
void usage()
{
    printf(1, "frisbee [thread count] [pass count]\n");
}

/// @brief prints an integer val to terminal
void print_int(int const val)
{
    printf(1, "%d\n", val);
}

/// @brief returns true if the provided character val is a
/// whitespace character. Otherwise, returns false.
int is_whitespace(char const val)
{
    switch (val)
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
int to_int(char const *const str)
{
    int ret = 0;
    if (!str)
        return ret;
    int i = 0;
    // advance over whitespace
    while (str[i] && is_whitespace(str[i]))
    {
        ++i;
    }
    while (str[i])
    {
        ret *= 10;
        ret += (int)(str[i] - '0');
        ++i;
    }
    return ret;
}

int main(int argc, char *argv[])
{
    int const expected_argument_count = 3;
    // assert expected argument count
    if (argc != expected_argument_count)
    {
        usage();
        exit();
    }
    // unpack user agruments
    int const thread_count_arg_idx = 1;
    char const *const thread_count_str = argv[thread_count_arg_idx];
    int const pass_count_arg_idx = 2;
    char const *const pass_count_str = argv[pass_count_arg_idx];
    // translate user arguments
    int const thread_count = to_int(thread_count_str);
    print_int(thread_count);
    int const pass_count = to_int(pass_count_str);
    print_int(pass_count);
    exit();
}
