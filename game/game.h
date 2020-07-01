#pragma once

#include <memory>
#include <vector>

#include "../strategies/interface.h"
#include "structures.h"

class game_t {
public:
  using player_t = std::shared_ptr<strategy_interface_t>;
  game_t(const player_t &first, const player_t &second) : field(){
      turns=0;
      players.push_back(first);
      players.push_back(second);
  };

  virtual void play() = 0;

protected:
  enum game_outcome_t {
    WIN,
    DRAW,
    IN_PROGRESS
  };


  field_t field; // поле игры
  std::vector<player_t> players; //игроки
  int turns;

private:
    virtual bool is_win_line(int x, size_t player_num) const = 0;
    virtual bool try_attack(const step_t &step, size_t player_num) = 0;
    virtual std::vector<step_t> opponents_near(int x, int y, bool queen, size_t player_num) = 0;
    virtual game_outcome_t is_win(size_t player_num) const = 0; //победа?
    virtual response_t apply_step(const step_t &step, size_t player_num) = 0;
};

