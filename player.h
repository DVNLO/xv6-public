#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

typedef struct
{
    int id;
    game_t * game;
} player_t;

int
get_player_id(player_t const * const player)
{
    return player->id;
}

void
set_player_id(player_t * const player, int const id_val)
{
    player->id = id_val;
}

int
get_game(player_t const * const player)
{
    return player->game;
}

void
set_game(player_t * const player, game_t const * const game_val)
{
    player->game = game_val;
}

#endif // PLAYER_H