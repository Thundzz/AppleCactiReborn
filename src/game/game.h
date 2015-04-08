#ifndef _GAME_H_
#define _GAME_H_
#include "tile.h"
/* The purpose of these structures is to serve as a data container,
   and are thusly declared in this header file.
   They've only been filled with a stub integer for the moment in 
   order to prevent the compiler from whining.
   TODO: Fill them with real content. 
*/
#define BOARD_SIZE 8


/*game data to be communicated to other modules (e.g. gui)*/
typedef struct game_s
{
  int board_size;
  tile_t board[BOARD_SIZE][BOARD_SIZE];
} game_t;

int game_init();
int game_start();
int game_over ();
int game_use_joker(joker_t * j);
int game_play_move(move_t * move);
int game_quit();

#endif
