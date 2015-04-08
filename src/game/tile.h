#ifndef _TILE_H_
#define _TILE_H_

typedef struct tile_s
{
  tile_content_t content;
  int exists;
} tile_t;

void tile_init(tile_t *t, tile_content_t content);
int tile_exists(tile_t *t);
int tile_destroyable(tile_t *t);
int tile_can_move_in(tile_t *t);

/* returns whatever is pushed out 
 * EMPTY moving in has no effect and pushes EMPTY out */
tile_content_t tile_move_in(tile_t *t, tile_content_t content);

/* returns true if trap set correctly, false if something was there. */
int tile_set_trap(tile_t *t);

tile_content_t tile_get_content(tile_t *t);
void  tile_set_content(tile_t *t, tile_content_t content);
void tile_destroy(tile_t *t);
void tile_steamroll(tile_t *t);

#endif
