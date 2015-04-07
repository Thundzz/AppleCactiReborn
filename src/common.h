#ifndef _COMMON_H_
#define _COMMON_H_

#define NB_PLAYER 2

typedef enum{
  VOID, //this tile has been destroyed
  EMPTY,
  APPLE,
  CACTUS,
  TRAP,
  NB_TILE_CONTENT
} tile_content_t;

typedef enum{
  JOKER_CHARGE,
  JOKER_PROCRASTINATION,
  JOKER_CORRUPTION,
  JOKER_STEAMROLLER,
  JOKER_TRAP,
  JOKER_REINFORCEMENT,
  NB_JOKER
} joker_t;

typedef enum{
  UP, RIGHT, DOWN, LEFT, NB_DIRECTION
} direction_t;


struct move_s{
  direction_t direction;
};
typedef struct move_s move_t;

typedef int player_id;

#endif
