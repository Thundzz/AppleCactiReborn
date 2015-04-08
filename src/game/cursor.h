#ifndef _CURSOR_H_
#define _CURSOR_H_

/* a cursor abstraction to visit the board in some direction*/

typedef struct cursor_1d_s
{
  int *i;
  int _end, _begin;
  int     (*end)(struct cursor_1d_s *this);
  void   (*next)(struct cursor_1d_s *this);
  int (*getnext)(struct cursor_1d_s *this);
} cursor_1d_t;

typedef struct cursor_s
{
  cursor_1d_t i, j;
} cursor_t;

void    cursor_up(cursor_t *dst, int *i, int *j, int board_size);
void cursor_right(cursor_t *dst, int *i, int *j, int board_size);
void  cursor_down(cursor_t *dst, int *i, int *j, int board_size);
void  cursor_left(cursor_t *dst, int *i, int *j, int board_size);

void cursor_new(cursor_t *dst,  direction_t ld, int *i, int *j, int board_size);
#endif 
