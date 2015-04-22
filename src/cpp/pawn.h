#ifndef _PAWN_H_
#define _PAWN_H_

typedef enum {
  PAWN_NOTHING,
  PAWN_PAWN,
  PAWN_GOOFY
} pawn_type_t;


/* 
 * a regular pawn, the mother of all pawns.
 * moves in a direction if ordered to by his owner or if pushed by another pawn.
 */

class pawn_c
{
 public:
  virtual ~pawn();
  static pawn_c * make_pawn(pawn_type_t type, player_id_t owner);
  virtual void move(pawn_c * collider, move_decision_t move, player_id_t player);
#ifdef DISPLAY
  int get_img_id();
#endif //def DISPLAY

 private:
  pawn(player_id_t owner);
  player_id_t owner;
#ifdef DISPLAY
  int img_id;
#endif
};


/*
 * A goofy pawn. inverses orders.
 */
class goofy_pawn_c:public pawn_c
{  
};
#endif // _PAWN_H_
