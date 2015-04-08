#include "../common.h"
#include "game.h"
#include "tile.h"

void tile_init(tile_t *t, tile_content_t content)
{
  t->exists = 1;
  t->content = content;
}

int tile_exists(tile_t *t)
{
  return t->exists;
}

int tile_destroyable(tile_t *t)
{
  switch(t->content)
    {
    case APPLE:
    case CACTUS:
      return 0;
      break;
    default:
      return 1;
    }
}

int tile_can_move_in(tile_t *t)
{
  // i'm considering  the creation of a joker that might make some tiles inaccessible.
  (void) t; // avoid unused parameter warning
  return 1;
}

/* returns whatever is pushed out 
 * EMPTY moving in has no effect and pushes EMPTY out */
tile_content_t tile_move_in(tile_t *t, tile_content_t content)
{
  tile_content_t leaving;
  if(t->exists)
    {
      switch(content)
	{
	case APPLE:
	case CACTUS:
	  leaving = content;
	  t->content = content;
	  break;
	case TRAP:
	  tile_destroy(t);
	  tile_move_in(t, content);
	  // no break : TRAP and default share following operation(s)
	default:
	  leaving = EMPTY;
	  break;
	}
    }
  else
    {
      ;//animation : content falls in the distorted void
    }
  return leaving;
}

/* returns true if trap set correctly, false if something was there. */
int tile_set_trap(tile_t *t)
{
  if(t->exists && (t->content == EMPTY || t->content == TRAP))
    {
      t->content = TRAP;
      return 1;
    }
  else
    return 0;
}

tile_content_t tile_get_content(tile_t *t)
{
  if(t->exists)
      return t->content;
  else
    return VOID;
}
void tile_set_content(tile_t *t, tile_content_t content)
{
  if(t->exists) // a rather pointless check
    t->content = content;
}
void tile_destroy(tile_t *t)
{
  t->exists = 0;
  t->content = EMPTY;
  ; //animation : tile falls
}

void tile_steamroll(tile_t *t)
{
  tile_set_content(t, EMPTY);
}
