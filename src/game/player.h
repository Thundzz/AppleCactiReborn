struct player_s;
typedef struct player_s player_t;

typedef enum {HUMAN, NB_PLAYER_TYPE} player_type_t;

int player_get_move(player_t * p, move_t *m);
player_t *player_next();
int player_uses_joker(player_t *p, joker_t *joker);
void player_init(int howmany, ...);
player_id player_get_id(player_t *p);
