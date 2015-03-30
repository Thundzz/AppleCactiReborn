#ifndef _DIRECTION_H_
#define _DIRECTION_H_

typedef struct direction_1d_s
{
  int (*begin)(int board_size), (*end)(int board_size); /*be very careful, as the index can be increasing or decreasing, use index != end and not index < end*/
  int (*next)(int i);
} direction_1d_t;

typedef struct direction_s
{
  direction_1d_t i, j;
  int (*plain_index)(int i, int j, int board_size);
} direction_t;

void direction_up(direction_t *dst);
void direction_right(direction_t *dst);
void direction_down(direction_t *dst);
void direction_left(direction_t *dst);

#endif 
