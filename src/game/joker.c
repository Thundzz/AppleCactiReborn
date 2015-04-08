#include <stdio.h>
#include "../common.h"
#include "../texts.h"
#include "game.h"
#include "game_internal.h"
#include "joker.h"
#include "player.h"

void (*joker[NB_JOKER])(joker_t *joker, game_t *game);

int joker_handle(joker_t *j, game_t *game)
{
  if(j->type >= NB_JOKER)
    {
      invalid_move();
      return -1;
    }
  joker[j->type](j, game);
  return 0;
}

void joker_charge(joker_t *j, game_t *game)
{
  move_t move;
  UNUSED(game);
  move.direction = j->joker.charge.direction;
  game_play_move(&move);
  game_play_move(&move);
  player_next();
}

void joker_procrastination(joker_t *j, game_t *game)
{
  UNUSED(game);
  UNUSED(j);
  player_next();
}

void joker_corruption(joker_t *j, game_t *game)
{
  position_t *position = &j->joker.corruption.position;
  tile_t * target = &game->board[position->i][position->j];
  // check the position is valid. An externally developped IA might 
  // try to corrupt something else than an opponent pawn.
  if(tile_get_content(target) == current_opponent_pawn())
    {
      tile_set_content(target, current_player_pawn());
      ; //animation : transformation of the pawn
    }
  else
    invalid_move();
}

void joker_steamroller(joker_t *j, game_t *game)
{
  for(int i = 0; i < BOARD_SIZE; ++i)
    {
      ; // animation : a steamroller crosses row j of the board
      tile_steamroll(&game->board[i][j->joker.steamroller.j]);
    }
  //this might result in an empty row/column on the edges
  destroy_empty_edges();
}

void joker_trap(joker_t *j, game_t *game)
{
  position_t *position = &j->joker.trap.position;
  if(!tile_set_trap(&game->board[position->i][position->j]))
    invalid_move();
}

void joker_reinforcement(joker_t *j, game_t *game)
{
  UNUSED(j);
  UNUSED(game);
  //TODO
}


void joker_init()
{
  joker[JOKER_CHARGE] = joker_charge;
  joker[JOKER_PROCRASTINATION] = joker_procrastination;
  joker[JOKER_CORRUPTION] = joker_corruption;
  joker[JOKER_STEAMROLLER] = joker_steamroller;
  joker[JOKER_TRAP] = joker_trap;
  joker[JOKER_REINFORCEMENT] = joker_reinforcement;
}
