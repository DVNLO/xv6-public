#include "types.h"

#include "mmu.h"
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
is_game_on(game_t * const frisbee)
{
    return get_turn_count(frisbee) < get_max_turn_count(frisbee);
}

int
is_player_turn(player_t const * const player, game_t * const frisbee)
{
    return get_player_id(player) == get_current_player_id(frisbee);
}

void
play_turn(player_t const * const player, game_t * const frisbee)
{
    int const current_turn_count = get_turn_count(frisbee);
    int const current_player_id = get_player_id(player);
    int const next_player_id
        = (current_player_id + 1) % get_player_count(frisbee);
    printf(1,
           "Pass number no: %d, Thread %d is passing the token to thread %d\n",
           current_turn_count, current_player_id, next_player_id);
    set_current_player_id(frisbee, next_player_id);
    int const next_turn_count = current_turn_count + 1;
    set_turn_count(frisbee, next_turn_count);
}

void *
play_frisbee(void * arg)
{
    player_t * const player = (player_t *)(arg);
    game_t * const frisbee = get_game(player);
    while(true)
    {
        // lock_acquire(get_lock(frisbee));
        if(!is_game_on(frisbee))
        {
            break;
        }
        if(is_player_turn(player, frisbee))
        {
            play_turn(player, frisbee);
        }
        // lock_release(get_lock(frisbee));
    }
    exit();
    return 0; // for compiler
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
    // construct frisbee game
    game_t frisbee;
    set_current_player_id(&frisbee, 0);
    set_player_count(&frisbee, player_count);
    set_turn_count(&frisbee, 0);
    set_max_turn_count(&frisbee, max_pass_count);
    // construct players
    player_t * players = malloc(sizeof(player_t) * get_player_count(&frisbee));
    if(!players)
    {
        printf(1, "unable to malloc players\n");
        exit();
    }
    int const player_stack_sz = PGSIZE;
    void * player_stack = malloc(sizeof(char) * player_stack_sz);
    printf(1, "user : player_stack : %p\n", (char *)(player_stack));
    int rc = clone(player_stack, player_stack_sz);
    printf(1, "rc : %d\n", rc);
    /*
    for(int i = 0; i < player_count; ++i)
    {
        void * player_stack = malloc(sizeof(char) * player_stack_sz);
        printf(1, "user : player_stack : %p\n", (char *)(player_stack));
        int rc = clone(player_stack, player_stack_sz);
        printf(1, "rc : %d\n", rc);
        if(rc < 0)
        {
            printf(1, "unable to malloc player stack\n");
            exit();
        }
        else if(rc > 0)
        {
            printf(1, "parent : %d\n", rc);
        }
        else
        {
            printf(1, "child : %d\n", rc);
        }
        player_t * current_player = &players[i];
        set_player_id(current_player, i);
        set_game(current_player, &frisbee);
    }
    */
    // spawn child threads
    /*
    for(int i = 0; i < player_count; ++i)
    {
        player_t * current_player = &players[i];
        thread_create(play_frisbee, (void *)(current_player))
    }
    */
    // thread_create(void*(*start_routine)(void*), void *arg)
    while(true)
    {
        if(!is_game_on(&frisbee))
        {
            break;
        }
        for(int i = 0; i < player_count; ++i)
        {
            play_frisbee(&players[i]);
        }
    }
    // wait for child threads to join
    exit();
}
