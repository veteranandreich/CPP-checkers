#include "computer_interface.h"

#include <cassert>
#include <iostream>

computer_interface_t::computer_interface_t() :
        win_counter{0},
        lose_counter{0},
        draw_counter{0} {}

void computer_interface_t::on_win() {
    ++win_counter;
}

void computer_interface_t::on_lose() {
    ++lose_counter;
}

void computer_interface_t::on_draw() {
    ++draw_counter;
}

void computer_interface_t::on_incorrect_step(const step_t &step, field_t &field, size_t player_num) const {
    field.print_field();
    std::cout << step.from_x << " " << step.from_y << " " << step.to_x << " " << step.to_y << " " << step.queen << " "<< player_num
              << std::endl;
    assert(false);
}

void computer_interface_t::print_stat() const {
    std::cout << "Wins:  " << win_counter << std::endl;
    std::cout << "Loses: " << lose_counter << std::endl;
    std::cout << "Draws:  " << draw_counter << std::endl;
    std::cout << std::endl;
}
