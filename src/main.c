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
  game_t *game = game_init();
  gui_t *gui = gui_init(game);

  while(!quit)
    {
      game_start(game);
      while(!game_over(game))
	{
	  while(gui_player_uses_joker(gui, &joker))
	    game_use_joker(game, &joker, player);
	  gui_get_move(gui, &move, player);
	  game_log_move(game, &mlog, &move);
	  gui_show_move(gui, &mlog);
	  game_play_move(game, &move);
	  player = player_next(player);
	}
      quit = gui_wannaplayagain(gui);
    }

  /* freeing resources */
  gui_quit(gui);
  game_quit(game);

  return EXIT_SUCCESS;
}
