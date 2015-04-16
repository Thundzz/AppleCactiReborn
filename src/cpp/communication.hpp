#ifndef _COMMUNICATION_HPP_
#define _COMMUNICATION_HPP_

#define TODO int unused_do_not_remove;
/*
 * A set of datatypes (struct/union) used for communication between modules.
 */

typedef enum{
  APPLE,
  CACTUS
} player_id_t;

typdef enum{
  UP,
  LEFT,
  DOWN,
  RIGHT
} direction_t;

typedef enum {
  JOKER_CHARGE,
  JOKER_PROCRASTINATION,
  JOKER_CORRUPTION,
  JOKER_STEAMROLLER,
  JOKER_TRAP,
  JOKER_REINFORCEMENT,
  NB_JOKER
} joker_type_t;

typedef enum {JOKER, MOVE, FORFEIT} decision_type_t;

typedef struct {
  decision_type_t type; // = JOKER
  TODO;
} joker_decision_t;
typedef struct{
  decision_type_t type; // = MOVE
  direction_t direction;
} move_decision_t;

/* A player's decision for one turn of his */
union decision_t{
  decision_type_t type;
  /*hack : all the following struct types must have as first member
   * decision_type_t type; this way decision_t's type and any other
   * member can be simultaneously assigned harmlessly.
   */
  joker_decision_t joker;
  move_decision_t move;
}

#endif
