#ifndef _GUI_H_
#define _GUI_H_

#include "game.h"

struct gui_s;
typedef struct gui_s gui_t;

gui_t * gui_init(game_t *game);
int gui_player_uses_joker(gui_t * g, joker_t *joker);
int gui_get_move(gui_t *g, move_t * move, player_id player);
int gui_show_move(gui_t*g, move_log_t * mlog);
int gui_wannaplayagain(gui_t *g);
int gui_quit(gui_t * g);
int gui_info(char *msg);
int gui_status(char *msg);

#endif
