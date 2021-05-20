typedef struct
{
    int current_player_id;
    int player_count;
    int turn_count;
    int max_turn_count;
} game_t;

int
get_current_player_id(game_t const * const game)
{
    return game->current_player_id;
}

void
set_current_player_id(game_t * const game, int const player_id)
{
    game->current_player_id = player_id;
}

int
get_player_count(game_t const * const game)
{
    return game->player_count;
}

void
set_player_count(game_t * const game, int const player_count_val)
{
    game->player_count = player_count_val;
}

int
get_turn_count(game_t const * const game)
{
    return game->turn_count;
}

void
set_turn_count(game_t * const game, int const turn_count_val)
{
    game->turn_count = turn_count_val;
}

int
get_max_turn_count(game_t const * const game)
{
    return game->max_turn_count;
}

void
set_max_turn_count(game_t * const game, int const max_turn_count_val)
{
    game->max_turn_count = max_turn_count_val;
}