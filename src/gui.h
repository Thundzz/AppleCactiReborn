#ifndef _GUI_H_
#define _GUI_H_

#include "game.h"

enum{GUI_OK, GUI_ERROR = -1};

int gui_init();
int gui_player_uses_joker(joker_t *joker);
int gui_get_move(move_t * move, player_id player);
int gui_show_move(move_log_t * mlog);
int gui_wannaplayagain();
int gui_quit();
int gui_info(char *msg);
int gui_status(char *msg);

#endif
