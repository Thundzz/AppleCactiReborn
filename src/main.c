#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "game/player.h"
#include "game/game.h"
#include "gui/gui.h"

int main(int argc, char*argv[])
{
  move_t move;
  joker_t joker;
  int quit = 0;

  /* initialisation */
  game_init();
  gui_init();
  player_init(NB_PLAYER, HUMAN, HUMAN);
  while(!quit)
    {
      printf("starting a new game\n");
      game_start();
      gui_draw();
      while(!game_over())
	{
	  printf("in main loop\n");
	  while(player_uses_joker(player_current(), &joker))
	    game_use_joker(&joker);
	  player_get_move(player_current(), &move);
	  game_play_move(&move);
	  gui_draw();
	  player_next();
	}
      printf("game ended\n");
      quit = !gui_wannaplayagain();
    }

  /* freeing resources */
  gui_quit();
  game_quit();

  return EXIT_SUCCESS;
}
