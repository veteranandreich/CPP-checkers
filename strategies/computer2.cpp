#include "computer2.h"

#include <iostream>
#include <vector>


computer_strategy_t::computer_strategy_t(std::string name) :
        name(std::move(name)) {}

step_t computer_strategy_t::make_step(const field_t &fld, const size_t player_num) {
    std::vector<step_t> possible_moves;
    possible_moves = find_moves(fld, player_num);

    if (possible_moves.empty()) {
        return {-228, -228, -228, -228};
    }


    return possible_moves[0];
}

void computer_strategy_t::print_stat() const {
    std::cout << "Strategy model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}

std::vector<step_t> computer_strategy_t::find_moves(const field_t &field, const size_t player_num) {
    char mark;
    char queen_mark;
    std::vector<step_t> moves;

    if (player_num == 0) {
        mark = field.player1_mark;
        queen_mark = field.player1_queen_mark;
    } else {
        mark = field.player2_mark;
        queen_mark = field.player2_queen_mark;
    }

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            std::vector<step_t> attack_moves;
            if (field.fld[y][x] == mark) {
                attack_moves = opponents_near(x, y, false, player_num, field);
                if (player_num == 0) {
                    if (field.is_reachable(x + 1, y + 1, x, y) && field.fld[y - 1][x - 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x, y);
                    }
                    if (field.is_reachable(x + 1, y + 1, x + 2, y) && field.fld[y - 1][x + 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x + 2, y);
                    }
                } else {
                    if (field.is_reachable(x + 1, y + 1, x, y + 2) && field.fld[y + 1][x - 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x, y + 2);
                    }
                    if (field.is_reachable(x + 1, y + 1, x + 2, y + 2) && field.fld[y + 1][x + 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x + 2, y + 2);
                    }
                }
            }
            if (field.fld[y][x] == queen_mark) {
                attack_moves = opponents_near(x, y, true, player_num, field);
                if (player_num == 0) {
                    if (field.is_reachable(x + 1, y + 1, x, y) && field.fld[y - 1][x - 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x, y, true);
                    }
                    if (field.is_reachable(x + 1, y + 1, x + 2, y) && field.fld[y - 1][x + 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x + 2, y, true);
                    }
                    if (field.is_reachable(x + 1, y + 1, x, y + 2) && field.fld[y + 1][x - 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x, y + 2, true);
                    }
                    if (field.is_reachable(x + 1, y + 1, x + 2, y + 2) && field.fld[y + 1][x + 1] == '.') {
                        moves.emplace_back(x + 1, y + 1, x + 2, y + 2, true);
                    }
                }
            }

            if (!attack_moves.empty()) {
                moves.insert(moves.begin(), attack_moves.begin(), attack_moves.end());
            }
        }
    }

    return moves;
}

std::vector<step_t>
computer_strategy_t::opponents_near(int x, int y, bool queen, size_t player_num, const field_t &field) {
    std::vector<step_t> opponents;

    char mark;
    char queen_mark;
    char opponent_mark;
    char opponent_queen_mark;

    if (player_num == 0) {
        mark = field.player1_mark;
        queen_mark = field.player1_queen_mark;
        opponent_mark = field.player2_mark;
        opponent_queen_mark = field.player2_queen_mark;
    } else {
        mark = field.player2_mark;
        queen_mark = field.player2_queen_mark;
        opponent_mark = field.player1_mark;
        opponent_queen_mark = field.player1_queen_mark;
    }

    if (!queen) {
        if (field.is_reachable(x + 1, y + 1, y - 1, x - 1) && (field.fld[y - 2][x - 2] == '.') &&
            (field.fld[y - 1][x - 1] == opponent_mark || field.fld[y - 1][x - 1] == opponent_queen_mark)) {
            opponents.emplace_back(x + 1, y + 1, x - 1, y - 1);
        }

        if (field.is_reachable(x + 1, y + 1, y - 1, x + 3) && (field.fld[y - 2][x + 2] == '.') &&
            (field.fld[y - 1][x + 1] == opponent_mark || field.fld[y - 1][x + 1] == opponent_queen_mark)) {
            opponents.emplace_back(x + 1, y + 1, x + 3, y - 1);
        }

        if (field.is_reachable(x + 1, y + 1, y + 3, x - 1) && (field.fld[y + 2][x - 2] == '.') &&
            (field.fld[y + 1][x - 1] == opponent_mark || field.fld[y + 1][x - 1] == opponent_queen_mark)) {
            opponents.emplace_back(x + 1, y + 1, x - 1, y + 3);
        }

        if (field.is_reachable(x + 1, y + 1, y + 3, x + 3) && (field.fld[y + 2][x + 2] == '.') &&
            (field.fld[y + 1][x + 1] == opponent_mark || field.fld[y + 1][x + 1] == opponent_queen_mark)) {
            opponents.emplace_back(x + 1, y + 1, x + 3, y + 3);
        }
    } else {
        bool ul = false; //нашли ли мы шашку противника в этом направлении, если нашли то дальше не ищем, тк нужно бить ближайшую
        bool ur = false;
        bool dl = false;
        bool dr = false;
        for (int i = 1; i < 8; i++) {

            if (!ul && y - i - 1 >= 0 && x - i - 1 >= 0 && field.fld[y - i - 1][x - i - 1] == '.' &&
                (field.fld[y - i][x - i] == opponent_mark || field.fld[y - i][x - i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1,  x - i, y - i, true);
                ul = true;
            }
            if (!ul && y - i - 1 >= 0 && x - i - 1 >= 0 && field.fld[y - i - 1][x - i - 1] == '.' &&
                (field.fld[y - i][x - i] == mark || field.fld[y - i][x - i] == queen_mark)) {
                ul = true;
            }


            if (!ur && y - i - 1 >= 0 && x + i + 1 <= 7 && field.fld[y - i - 1][x + i + 1] == '.' &&
                (field.fld[y - i][x + i] == opponent_mark || field.fld[y - i][x + i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1, x + i + 2, y - i, true);
                ur = true;
            }
            if (!ur && y - i - 1 >= 0 && x + i + 1 <= 7 && field.fld[y - i - 1][x + i + 1] == '.' &&
                (field.fld[y - i][x + i] == mark || field.fld[y - i][x + i] == queen_mark)) {
                ur = true;
            }

            if (!dl && y + i + 1 <= 7 && x - i - 1 >= 0 && field.fld[y + i + 1][x - i - 1] == '.' &&
                (field.fld[y + i][x - i] == opponent_mark || field.fld[y + i][x - i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1,  x - i, y + i + 2, true);
                dl = true;
            }
            if (!dl && y + i + 1 <= 7 && x - i - 1 >= 0 && field.fld[y + i + 1][x - i - 1] == '.' &&
                (field.fld[y + i][x - i] == mark || field.fld[y + i][x - i] == queen_mark)) {
                dl = true;
            }


            if (!dr && y + i + 1 <= 7 && x + i + 1 <= 7 && field.fld[y + i + 1][x + i + 1] == '.' &&
                (field.fld[y + i][x + i] == opponent_mark || field.fld[y + i][x + i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1,  x + i + 2, y + i + 2, true);
                dr = true;
            }
            if (!dr && y + i + 1 <= 7 && x + i + 1 <= 7 && field.fld[y + i + 1][x + i + 1] == '.' &&
                (field.fld[y + i][x + i] == mark || field.fld[y + i][x + i] == queen_mark)) {
                dr = true;
            }
        }
    }
    return opponents;
}
