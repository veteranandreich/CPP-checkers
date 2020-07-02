#pragma once

#include "../game/structures.h"

class strategy_interface_t {
public:
    virtual step_t make_step(const field_t &field, size_t player_num) = 0;

    virtual void on_incorrect_step(const step_t &step, field_t &field, size_t player_num)const = 0;

    virtual void on_lose() = 0;

    virtual void on_win() = 0;

    virtual void on_draw() = 0;
};
