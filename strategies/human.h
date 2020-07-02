#pragma once

#include "interface.h"

class human_strategy_t : public strategy_interface_t {
public:
    human_strategy_t();

    step_t make_step(const field_t &field, size_t player_num) override;

    void on_incorrect_step(const step_t &step, field_t &field, size_t player_num) const override;

    void on_win() override;

    void on_lose() override;

    void on_draw() override;
};
