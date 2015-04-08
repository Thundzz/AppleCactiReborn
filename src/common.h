#ifndef _COMMON_H_
#define _COMMON_H_

#define NB_PLAYER 2

/* ISO C does not allow empty structs. therefore, if nothing is needed in a struct,
 this macro will be used, declaring an unused element in the structure. */
#define EMPTY_STRUCT int unused_do_not_remove;

typedef enum{
  UP, RIGHT, DOWN, LEFT, NB_DIRECTION
} direction_t;

typedef enum{
  VOID, //this tile has been destroyed
  EMPTY,
  APPLE,
  CACTUS,
  TRAP,
  NB_TILE_CONTENT
} tile_content_t;

typedef struct position_s{
  int i, j;
} position_t;

typedef enum{
  JOKER_CHARGE,
  JOKER_PROCRASTINATION,
  JOKER_CORRUPTION,
  JOKER_STEAMROLLER,
  JOKER_TRAP,
  JOKER_REINFORCEMENT,
  NB_JOKER
} joker_type_t;

typedef struct joker_charge_s{
  direction_t direction;
} joker_charge_t;

typedef struct joker_procrastination_s{
  EMPTY_STRUCT
} joker_procrastination_t;

typedef struct joker_corruption_s{
  position_t position;
} joker_corruption_t;

typedef struct joker_steamroller_s{
  int j;
} joker_steamroller_t;

typedef struct joker_trap_s{
  position_t position;
} joker_trap_t;

typedef struct joker_reinforcement_s{
  EMPTY_STRUCT
} joker_reinforcement_t;

typedef struct joker_s{
  joker_type_t type;
  union joker_u{
    joker_charge_t charge;
    joker_procrastination_t procrastination;
    joker_corruption_t corruption;
    joker_steamroller_t steamroller;
    joker_trap_t trap;
    joker_reinforcement_t reinforcement;
  } joker;
} joker_t;


struct move_s{
  direction_t direction;
};
typedef struct move_s move_t;

typedef int player_id;

#endif
