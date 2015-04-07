#include "../common.h"
#include "player.h"
#include "game.h"
#include "cursor.h"

static struct{
  int size;
  tile_content_t board[BOARD_SIZE][BOARD_SIZE]
    } board = {BOARD_SIZE, {{0}}};

int game_init(){
  return 0;
}


int game_start(){
  return 0;
}


int game_over (){
  return 1;
}


int game_use_joker(joker_t * j){
  return 0;
}

int tile_not_empty(tile_content_t t)
{
  return t == APPLE || t == CACTUS;
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
	      if(tile_not_empty(board.board[i][j]))
		destroy_line = 0;
	    }
	  for(; !cursor.j.end(&cursor.j) && destroy_line; cursor.j.next(&cursor.j))
	    board.board[i][j] = VOID;
	}
    }
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
	  if(board.board[i][j] == VOID)
	    {
	      //any incoming thing falls in the distorted void
	      tmp[j] = EMPTY;
	    }
	  else if(tmp[j] != EMPTY)
	    {
	      tile_content_t ttmp = tmp[j];
	      tmp[j] = board.board[i][j];
	      board.board[i][j] = ttmp;
	    }
	  else if(board.board[i][j] == moving)
	    {
	      tmp[j] = board.board[i][j];
	      board.board[i][j] = EMPTY;
	    }
	}
    }
  destroy_empty_edges();
  return 0;
}



int game_quit(){
  return 0;
}
