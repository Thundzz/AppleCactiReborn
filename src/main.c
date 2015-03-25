#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "player.h"
#include "game.h"
#include "gui.h"

int main(int argc, char*argv[])
{
  move_t move;
  joker_t joker;
  int quit = 0;
  player_t * p;

  /* initialisation */
  game_init();
  gui_init();
  player_init(NB_PLAYER, HUMAN, HUMAN);
  while(!quit)
    {
      printf("starting a new game\n");
      game_start();
      while(!game_over())
	{
	  printf("in main loop\n");
	  p = player_next();
	  while(player_uses_joker(p, &joker))
	    game_use_joker(&joker, p);
	  player_get_move(p, &move);
	  game_play_move(&move);
	  p = player_next();
	}
      printf("game ended\n");
      quit = !gui_wannaplayagain();
    }

  /* freeing resources */
  gui_quit();
  game_quit();

  return EXIT_SUCCESS;
}
