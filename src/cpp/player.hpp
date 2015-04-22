#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

class player_c{
public:
  // decide which joker to use / which move to play.
  virtual decision_t make_decision(game_state *state) = 0;
  player_id_t get_id();
  virtual ~player() = 0;
protected:
  player_id_t id;
};

class network_player_c : public player_c
{
public:
  network_player_c(player_id_t id);
  virtual decision_t make_decision(game_state_t *state);
  virtual player_id_t get_id();
  ~network_player_c();
}

#endif
