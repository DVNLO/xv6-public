#include "stat.h"
#include "types.h"
#include "user.h"

#define false 0
#define true 1

/// @brief prints frisbee usage to terminal
void
usage()
{
    printf(1, "frisbee [player count] [max pass count]\n");
}

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

int
is_turn(int const token, int const thread_id)
{
    return token == thread_id;
}

void
pass_token(int const pass_count, int * const token, int const from_thread_id,
           int const to_thread_id)
{
    *token = to_thread_id;
    printf(1,
           "Pass number no: %d, Thread %d is passing the token to thread %d",
           pass_count, from_thread_id, to_thread_id);
}

void
player(void * arg)
{
    game_t * frisbee = (game_t *)(arg);
    while(game_on(frisbee))
    {
        play(frisbee);
    }
}

int
main(int argc, char * argv[])
{
    int const expected_argument_count = 3;
    // assert expected argument count
    if(argc != expected_argument_count)
    {
        usage();
        exit();
    }
    // unpack user agruments
    char const * const player_count_str = argv[1];
    char const * const max_pass_count_str = argv[2];
    // translate user arguments
    int const player_count = to_int(player_count_str);
    int const max_pass_count = to_int(max_pass_count_str);
    // construct frisbee game;
    game_t frisbee;
    set_current_player_id(&frisbee, 0);
    set_player_count(&frisbee, player_count);
    set_turn_count(&frisbee, 0);
    set_max_turn_count(&frisbee, max_pass_count);

    // spawn child threads
    // wait for child threads to join
    exit();
}
