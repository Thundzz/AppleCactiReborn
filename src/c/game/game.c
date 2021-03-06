#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../common.h"
#include "../texts.h"
#include "player.h"
#include "game.h"
#include "game_internal.h"
#include "cursor.h"
#include "joker.h"

static game_t game;

game_t * game_get()
{
  return &game;
}
int game_init(){
  joker_init();
  srand(time(NULL));
  game.started = 0;
  return 0;
}

int random_int(int max)
{
  int retval = (((double)rand())/RAND_MAX*(max+1));
  if (retval > max) // sooo unlikely
    return max;
  return retval;
}

int game_start(){
  game.board_size = BOARD_SIZE;
  int nb_free_cells = BOARD_SIZE * BOARD_SIZE;
  for(int i = 0; i < NB_PLAYER; ++i)
    game.pawn_count[i] = nb_free_cells/2;
  int nb_free_cacti = nb_free_cells/2;
  for(; nb_free_cells--;)
    {
      int i = nb_free_cells / BOARD_SIZE;
      int j = nb_free_cells % BOARD_SIZE;
      if(random_int(nb_free_cells) >= nb_free_cacti)
	tile_init(&game.board[i][j], APPLE);
      else
	{
	  tile_init(&game.board[i][j], CACTUS);
	  --nb_free_cacti;
	}
    }
  return 0;
}


int game_over (){
  int nonzero = 0;
  for(int player = 0; player < NB_PLAYER; player++)
    {
      if(game.pawn_count[player] > 0)
	nonzero++;
    }
  return nonzero <= 1;
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
      cursor_new(&cursor, direction, &i, &j, game.board_size);
      for(; !cursor.i.end(&cursor.i) && destroy_line; cursor.i.next(&cursor.i))
	{
	  for(; !cursor.j.end(&cursor.j) && destroy_line; cursor.j.next(&cursor.j))
	    {
	      if(!tile_destroyable(&game.board[i][j]))
		destroy_line = 0;
	    }
	  if(destroy_line)
	    for(; !cursor.j.end(&cursor.j); cursor.j.next(&cursor.j))
	      {
		tile_destroy(&game.board[i][j]);
	      }
	}
    }
}

int game_use_joker(joker_t * j){
  return joker_handle(j, &game);
}

int game_one_pawn_down(tile_content_t pawn)
{
  switch(pawn)
    {
    case APPLE:
    case CACTUS:
      game.pawn_count[pawn-1]--;
      break;
    default:
      break;
    }
}

int game_play_move(move_t * move){
  cursor_t cursor;
  int i, j;
  tile_content_t moving = current_player_pawn();
  tile_content_t tmp[BOARD_SIZE];
  for(int k = 0; k < BOARD_SIZE; ++k)
    tmp[k] = EMPTY;
  cursor_new(&cursor, move->direction, &i, &j, game.board_size);
  for(; !cursor.i.end(&cursor.i); cursor.i.next(&cursor.i))
    {
      for(; !cursor.j.end(&cursor.j); cursor.j.next(&cursor.j))
	{
	  tile_t *current = &game.board[i][j];
	  if(tile_get_content(current) == moving)
	    {
	      tile_set_content(current, tmp[*(cursor.j.i)]);
	      tmp[*(cursor.j.i)] = moving;
	    }
	  else
	    {
	      tmp[*(cursor.j.i)] = tile_move_in(current, tmp[*(cursor.j.i)]);
	    }
	}
    }
  for(int k = 0; k < BOARD_SIZE; ++k)
    game_one_pawn_down(tmp[k]);
  destroy_empty_edges();
  return 0;
}

int game_quit(){
  return 0;
}
