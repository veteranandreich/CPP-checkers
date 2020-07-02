#include "human.h"

#include <iostream>

void human_strategy_t::on_win() {
    std::cout << "You win!" << std::endl;
}

void human_strategy_t::on_lose() {
    std::cout << "You lose!" << std::endl;
}

void human_strategy_t::on_draw() {
    std::cout << "Draw!" << std::endl;
}

step_t human_strategy_t::make_step(const field_t &fld, const size_t player_num) {

    fld.print_field();

    std::cout << "Type coordinates of movable checker (x y): " << std::endl;
    int from_x, from_y, to_x, to_y;
    bool queen = false;
    std::cin >> from_x >> from_y;
    std::cout << "Where to move?";
    std::cin >> to_x >> to_y;
    if (fld.is_reachable(from_x, from_y, to_x, to_y) &&
        (fld.fld[from_y - 1][from_x - 1] == fld.player1_queen_mark ||
         fld.fld[from_y - 1][from_x - 1] == fld.player2_mark)) {
        queen = true;
    }
    return {from_x, from_y, to_x, to_y, queen};
}

void human_strategy_t::on_incorrect_step(const step_t &step, field_t &field, size_t player_num) const {
    std::cout << "Incorrect step: from_x " << step.from_x << " from_y " << step.from_y << " to_x " << step.to_x << " to_y "
              << step.to_y;
}

human_strategy_t::human_strategy_t() : strategy_interface_t() {

}
