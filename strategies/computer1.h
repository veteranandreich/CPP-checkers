#pragma once

#include <string>
#include <vector>

#include "../game/structures.h"
#include "computer_interface.h"

class random_strategy_t : public computer_interface_t {
public:
    explicit random_strategy_t(std::string name);

    step_t make_step(const field_t &field, size_t player_num) override;

    void print_stat() const override;

private:
    std::string name;

    std::vector<step_t> find_moves(const field_t &field, size_t player_num) override;

    std::vector<step_t> opponents_near(int x, int y, bool queen, size_t player_num, const field_t &field) override;
};
