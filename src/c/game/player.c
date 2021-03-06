#include <stdarg.h>
#include <stdio.h>
#include "../common.h"
#include "game.h"
#include "player.h"
#include "../gui/gui.h"
#include "../texts.h"
struct player_s
{
  int (*get_move)(move_t *, player_id);
  int (*uses_joker)(joker_t *, player_id);
};

static player_t player[NB_PLAYER];
static int current_player_id = 0;

tile_content_t current_player_pawn()
{
  return current_player_id ? CACTUS : APPLE;
}
tile_content_t current_opponent_pawn()
{
  return current_player_id ? APPLE : CACTUS;
}
int player_get_move(player_t * p, move_t *m)
{
  return p->get_move(m, player_get_id(p));
}
void player_next()
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
}
player_t *player_current()
{
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
	  break;
	default:
	  fprintf(stderr, INVALID_PLAYER_TYPE, itype);
	}
    }
  va_end(ap);
}

player_id player_get_id(player_t *p)
{
  return p - player;
}
