#ifndef _GAME_H_
#define _GAME_H_

/* The purpose of these structures is to serve as a data container,
   and are thusly declared in this header file.
   They've only been filled with a stub integer for the moment in 
   order to prevent the compiler from whining.
   TODO: Fill them with real content. 
*/
#define BOARD_SIZE 8

typedef struct game_s game_t;


int game_init();
int game_start();
int game_over ();
int game_use_joker(joker_t * j);
int game_play_move(move_t * move);
int game_quit();

#endif
