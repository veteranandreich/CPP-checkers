#pragma once

#include "interface.h"
#include <vector>

class computer_interface_t : public strategy_interface_t {
public:
    computer_interface_t();

    void on_win() override;

    void on_lose() override;

    void on_draw() override;

    void on_incorrect_step(const step_t &step, field_t &field, size_t player_num) const override;

    virtual void print_stat() const;

protected:
    virtual std::vector<step_t> find_moves(const field_t &field, size_t player_num) = 0;
    virtual std::vector<step_t> opponents_near(int x, int y, bool queen, size_t player_num, const field_t &field) = 0;

private:
    size_t win_counter;
    size_t lose_counter;
    size_t draw_counter;
};
