#include <stdio.h>
#include "direction.h"

#define TEST_SIZE 3
int main(int argc, char * argv[])
{
  direction_t d[4];
  
  direction_up(d);
  direction_right(d+1);
  direction_down(d+2);
  direction_left(d+3);

  for(int irection = 0; irection < 4; ++irection)
    {
      for(int i = d[irection].i.begin(TEST_SIZE); i != d[irection].i.end(TEST_SIZE); i = d[irection].i.next(i))
	{
	  for(int j = d[irection].j.begin(TEST_SIZE); j != d[irection].j.end(TEST_SIZE); j = d[irection].j.next(j))
	    {
	      printf("%d ", d[irection].plain_index(i, j, TEST_SIZE));
	    }
	  printf("\n");
	}
      printf("\n");
    }
  return 0;
}
