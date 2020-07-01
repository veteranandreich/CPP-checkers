#pragma once

#include "game.h"
#include <vector>

class checker_game : public game_t{
public:
    using player_t = std::shared_ptr<strategy_interface_t>;

    checker_game(const checker_game::player_t &first, const checker_game::player_t &second) : game_t(first, second) {
    }

    void play() override;

private:
    bool is_win_line(int x, size_t player_num) const override;
    bool try_attack(const step_t &step, size_t player_num) override;
    std::vector<step_t> opponents_near(int x, int y, bool queen, size_t player_num) override;
    game_outcome_t is_win(size_t player_num) const override; //победа?
    response_t apply_step(const step_t &step, size_t player_num) override; //применить шаг
};