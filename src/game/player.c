#include <stdarg.h>
#include <stdio.h>
#include "../common.h"
#include "game.h"
#include "player.h"
#include "../gui/gui.h"

struct player_s
{
  int (*get_move)(move_t *, player_id);
  int (*uses_joker)(joker_t *, player_id);
};

static player_t player[NB_PLAYER];
int current_player_id = 0;

int player_get_move(player_t * p, move_t *m)
{
  return p->get_move(m, player_get_id(p));
}
player_t *player_next()
{
#if NB_PLAYER == 2
  //neat optimization for higher performance
  current_player_id = 1 - current_player_id;
  //todo benchmark to see if performance is better with :
  // current_player_id = !current_player_id;
#else
  current_player_id++;
  if(current_player_id == NB_PLAYERS)
    current_player_id = 0;
#endif

  return player + current_player_id;
}
int player_uses_joker(player_t *p, joker_t *joker)
{
  return p->uses_joker(joker, player_get_id(p));
}

void player_init_human(player_t * p)
{
  p->get_move = gui_get_move;
  p->uses_joker = gui_player_uses_joker;
}

void player_init(int howmany, ...)
{
  /*howmany must be NB_PLAYER, but a variadic function requires at least one explicit argument, so well.*/
  va_list ap;
  player_id i = howmany;
  player_type_t itype;
  va_start(ap, howmany);
  while(i--)
    {
      itype = va_arg(ap, player_type_t);
      switch(itype)
	{
	case HUMAN:
	  player_init_human(player+i);
	default:
	  fprintf(stderr, "Failed to init a player of type %d.\n", itype);
	}
    }
  va_end(ap);
}

player_id player_get_id(player_t *p)
{
  return p - player;
}
