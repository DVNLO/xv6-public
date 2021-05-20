#include "types.h"

#include "stat.h"
#include "user.h"

#include "game.h"
#include "player.h"
#include "utility.h"

/// @brief prints frisbee usage to terminal
void
usage()
{
    printf(1, "frisbee [player count] [max pass count]\n");
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
    // construct players

    // spawn child threads
    // wait for child threads to join
    exit();
}
