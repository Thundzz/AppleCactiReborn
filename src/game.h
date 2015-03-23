#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"

/* The purpose of these structures is to serve as a data container,
   and are thusly declared in this header file.
   They've only been filled with a stub integer for the moment in 
   order to prevent the compiler from whining.
   TODO: Fill them with real content. 
*/

typedef int player_id;

struct move_s{
  int stub;
};
typedef struct move_s move_t;

struct game_s{
  int stub;
};
typedef struct game_s game_t;

struct move_log_s{
  int stub;
};

typedef struct move_log_s move_log_t;


game_t * game_init();
int      game_start(game_t * game);
int      game_over (game_t * game);
int      game_use_joker(game_t * g, joker_t * j, player_id p);
int      game_log_move (game_t * g, move_log_t * mlg,  move_t *m);
int	 game_play_move(game_t * g, move_t * move);
int	 game_quit(game_t * g);
	


#endif