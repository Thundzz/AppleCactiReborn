#include <stdio.h>
#include <stdlib.h>
#include "gui.h"
#include "game.h"


player_id player_next(int current)
{
  return 1-current;
}

int main(int argc, char*argv[])
{
  move_t move;
  move_log_t mlog;
  joker_t joker;
  player_id player = 0, quit = 0;

  /* initialisation */
  game_init();
  gui_init();

  while(!quit)
    {
      printf("starting a new game\n");
      game_start();
      while(!game_over())
	{
	  printf("in main loop\n");
	  while(gui_player_uses_joker(&joker))
	    game_use_joker(&joker, player);
	  gui_get_move(&move, player);
	  game_log_move(&mlog, &move);
	  gui_show_move(&mlog);
	  game_play_move(&move);
	  player = player_next(player);
	}
      printf("game ended\n");
      quit = !gui_wannaplayagain();
    }

  /* freeing resources */
  gui_quit();
  game_quit();

  return EXIT_SUCCESS;
}
