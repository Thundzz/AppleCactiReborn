#include "direction.h"

int direction_1d_incr(int i)
{
  return i+1;
}
int direction_1d_decr(int i)
{
  return i-1;
}
int direction_1d_begin(int board_size)
{
  return 0;
}
int direction_1d_rbegin(int board_size)
{
  return board_size - 1;
}

int direction_1d_end(int board_size)
{
  return board_size;
}
int direction_1d_rend(int board_size)
{
  return -1;
}

void direction_1d_left(direction_1d_t *dst)
{
  dst->begin = direction_1d_begin;
  dst->end = direction_1d_end;
  dst->next = direction_1d_incr;
}
void direction_1d_right(direction_1d_t *dst)
{
  dst->begin = direction_1d_rbegin;
  dst->end = direction_1d_rend;
  dst->next = direction_1d_decr;
}


int innermost_i(int i, int j, int size)
{
  return j*size+i;
}

int innermost_j(int i, int j, int size)
{
  return i*size+j;
}
/* (0,0) top left ; (max, max) bottom right */

void direction_left(direction_t *dst)
{
  direction_1d_right(&dst->i);
  direction_1d_left(&dst->j);
  dst->plain_index = innermost_i;
}
void direction_up(direction_t *dst)
{
  direction_1d_right(&dst->i);
  direction_1d_right(&dst->j);
  dst->plain_index = innermost_j;
}
void direction_right(direction_t *dst)
{
  direction_1d_left(&dst->i);
  direction_1d_right(&dst->j);
  dst->plain_index = innermost_i;
}
void direction_down(direction_t *dst)
{
  direction_1d_left(&dst->i);
  direction_1d_left(&dst->j);
  dst->plain_index = innermost_j;
}

