#include <stdio.h>
#include "../common.h"
#include "player.h"
#include "game.h"
#include "cursor.h"
#include "../texts.h"

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
	      if(tile_not_empty(board.board[i][j]))
		destroy_line = 0;
	    }
	  for(; !cursor.j.end(&cursor.j) && destroy_line; cursor.j.next(&cursor.j))
	    board.board[i][j] = VOID;
	}
    }
}

int game_use_joker(joker_t * j){
  move_t move;
  position_t *position;
  switch(j->type)
    {
    case JOKER_CHARGE:
      move.direction = j->joker.charge.direction;
      game_play_move(&move);
      game_play_move(&move);
      //no break, following code common to charge and procrastination
    case JOKER_PROCRASTINATION:
      player_next();
      break;
    case JOKER_CORRUPTION:
      position = &j->joker.corruption.position;
      // check the position is valid. An externally developped IA might 
      // try to corrupt something else than an opponent pawn.
      if(board.board[position->i][position->j] == current_opponent_pawn())
	board.board[position->i][position->j] = current_player_pawn();
      ; //animation : transformation of the pawn
      else
	invalid_move();
      break;
    case JOKER_STEAMROLLER:
      for(int i = 0; i < BOARD_SIZE; ++i)
	{
	  ; // animation : a steamroller crosses row j of the board
	  if(board.board[i][j->joker.steamroller.j] != VOID)
	    board.board[i][j->joker.steamroller.j] = EMPTY;
	}
      //this might result in an empty row/column on the edges
      destroy_empty_edges();
      break;
    case JOKER_TRAP:
      position = &j->joker.trap.position;
      if(board.board[position->i][position->j] != EMPTY)
	invalid_move();
      else
	board.board[i][j] = TRAP;
      break;
    case JOKER_REINFORCEMENT:
      break;
    default:
      fputs(ERROR_YOUDONWANNANO, stderr);
      break;
    }
  return 0;
}

/* used to determine when to remove a column/line (if there's no pawn on it) */
int tile_not_empty(tile_content_t t) 
{
  return t == APPLE || t == CACTUS;
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
	  if(board.board[i][j] == TRAP)
	    {
	      board.board[i][j] = VOID;
	      ; //animation : trap revealed
	    }
	  if (board.board[i][j] == VOID)
	    {
	      //any incoming thing falls in the distorted void
	      if (tmp[j] != EMPTY)
		{
		  ;//falling animation
		  tmp[j] = EMPTY;
		}
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
