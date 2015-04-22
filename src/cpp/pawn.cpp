#ifdef DISPLAY
#include "image.h"
#endif
#include "pawn.h"

pawn_c::make_pawn(pawn_type_t type, player_id_t owner)
{
  switch(type)
    {
    case PAWN_NOTHING:
      return new pawn_nothing_c(owner);
      break;
    case PAWN_GOOFY:
      return new goofy_pawn_c(owner);
      break;
    case PAWN_PAWN:
    default:
      return new pawn_c(owner);
      break;
    }
}

pawn::pawn(player_id_t owner)
{
  this->owner = owner;
#ifdef DISPLAY
  this->img_id = img::chose_pawn(IMG_PAWN, owner);
#endif
}
