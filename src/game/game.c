#include <stdio.h>
#include "../common.h"
#include "../texts.h"
#include "player.h"
#include "game.h"
#include "cursor.h"
#include "joker.h"

static game_t game;

game_t * game_get()
{
  return &game;
}
int game_init(){
  joker_init();
  return 0;
}


int game_start(){
  return 0;
}


int game_over (){
  return 1;
}

void invalid_move()
{
  fputs(INVALID_MOVE, stderr);
  // the current player made an invalid move (likely a bug). His opponent wins.
  //TODO  
}

/* Empty lines/columns on the edges of the board fall apart */
void destroy_empty_edges()
{
  for(int direction = 0; direction < NB_DIRECTION; ++direction)
    {
      int i, j;
      cursor_t cursor;
      int destroy_line = 1;
      cursor_new(&cursor, direction, &i, &j, board.size);
      for(; !cursor.i.end(&cursor.i) && destroy_line; cursor.i.next(&cursor.i))
	{
	  for(; !cursor.j.end(&cursor.j) && destroy_line; cursor.j.next(&cursor.j))
	    {
	      if(tile_destroyable(&game.board[i][j]))
		destroy_line = 0;
	    }
	  for(; !cursor.j.end(&cursor.j); cursor.j.next(&cursor.j))
	    tile_destroy(&game.board[i][j]);
	}
    }
}

int game_use_joker(joker_t * j){
  return joker_handle(j, &game);
}

int game_play_move(move_t * move){
  cursor_t cursor;
  int i, j;
  tile_content_t moving = current_player_pawn();
  tile_content_t tmp[BOARD_SIZE];
  for(int k = 0; k < BOARD_SIZE; ++k)
    tmp[k] = EMPTY;
  cursor_new(&cursor, move->direction, &i, &j, board.size);
  for(; !cursor.i.end(&cursor.i); cursor.i.next(&cursor.i))
    {
      for(; !cursor.j.end(&cursor.j); cursor.j.next(&cursor.j))
	{
	  tile_t *current = &game.board[i][j];
	  tmp[j] = tile_move_in(current, tmp[j]);
	  if(tile_get_content(current) == moving)
	    {
	      tmp[j] = moving;
	      tile_set_content(current, EMPTY);
	    }
	}
    }
  destroy_empty_edges();
  return 0;
}

int game_quit(){
  return 0;
}
