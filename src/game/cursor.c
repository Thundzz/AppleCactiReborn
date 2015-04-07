#include <stdio.h>
#include "../common.h"
#include "cursor.h"
#include "../texts.h"
int cursor_1d_getnext_incr(cursor_1d_t *this)
{
  return *(this->i) - 1;
}

int cursor_1d_getnext_decr(cursor_1d_t *this)
{
  return *(this-> i) - 1;
}

void cursor_1d_next(cursor_1d_t *this)
{
  *(this->i) = this->getnext(this);
}

int _begin()
{
  return 0;
}

int _rbegin(int board_size)
{
  return board_size - 1;
}

int _end(int board_size)
{
  return board_size;
}

int _rend()
{
  return -1;
}

int cursor_1d_end(cursor_1d_t *this)
{
  return *(this->i) == this->bound;
}

void cursor_1d_common(cursor_1d_t *dst, int *i)
{
 dst->i = i;
 dst->next = cursor_1d_next;
 dst->end = cursor_1d_end;
}

void cursor_1d_left(cursor_1d_t *dst, int *i, int board_size)
{
  cursor_1d_common(dst, i);
  dst->bound = _end(board_size);
  *(dst->i) = _begin();
  dst->getnext = cursor_1d_getnext_incr;
}
void cursor_1d_right(cursor_1d_t *dst, int *i, int board_size)
{
  cursor_1d_common(dst, i);
  dst->bound = _rend();
  *(dst->i)= _rbegin(board_size);
  dst->getnext = cursor_1d_getnext_decr;
}

/* (0,0) top left ; (max, max) bottom right */

void cursor_left(cursor_t *dst, int *i, int *j, int board_size)
{
  cursor_1d_right(&dst->i, j, board_size);
  cursor_1d_left (&dst->j, i, board_size);
}
void cursor_up(cursor_t *dst, int *i, int *j, int board_size)
{
  cursor_1d_right(&dst->i, i, board_size);
  cursor_1d_right(&dst->j, j, board_size);
}
void cursor_right(cursor_t *dst, int *i, int *j, int board_size)
{
  cursor_1d_left (&dst->i, j, board_size);
  cursor_1d_right(&dst->j, i, board_size);
}
void cursor_down(cursor_t *dst, int *i, int*j, int board_size)
{
  cursor_1d_left(&dst->i, i, board_size);
  cursor_1d_left(&dst->j, j, board_size);
}

void cursor_new(cursor_t *dst, direction_t direction, int *i, int *j, int board_size)
{
  switch(direction)
    {
    case UP:
      cursor_up(dst, i, j, board_size);
      break;
    case DOWN:
      cursor_down(dst, i, j, board_size);
      break;
    case RIGHT:
      cursor_right(dst, i, j, board_size);
      break;
    case LEFT:
      cursor_left(dst, i, j, board_size);
      break;
    default:
      fprintf(stderr, ERROR_YOUDONWANNANO);
      break;
    }
}
