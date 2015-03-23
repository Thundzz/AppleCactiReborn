#ifndef _COMMON_H_
#define _COMMON_H_

#define NB_PLAYER 2

typedef enum{
  VOID, EMPTY, APPLE, CACTUS, TRAP, NB_SQUARE_CONTENT
} square_content_t;

typedef enum{
  CHARGE, PROCRASTINATION, CORRUPTION, STEAMROLLER, TRAP_J, REINFORCEMENT, NB_JOKER
} joker_t;

typedef enum{
  TOP, RIGHT, BOTTOM, LEFT
} direction_t;

#endif
