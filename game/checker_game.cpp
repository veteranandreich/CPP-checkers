#include "checker_game.h"
#include <cmath>
#include <set>


response_t checker_game::apply_step(const step_t &step, size_t player_num) {
    char &to_cell = field.fld[step.to_y - 1][step.to_x - 1];
    char &from_cell = field.fld[step.from_y - 1][step.from_x - 1];

    if (!field.is_reachable(step)) {
        return false;
    }

    char mark;
    char queen_mark;

    if (player_num == 0) {
        mark = field.player1_mark;
        queen_mark = field.player1_queen_mark;
    } else {
        mark = field.player2_mark;
        queen_mark = field.player2_queen_mark;
    }

    std::vector<step_t> opponents;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (field.fld[y][x]==mark) {
                std::vector<step_t> attack_moves = opponents_near(x, y, false, player_num);
                opponents.insert(opponents.end(), attack_moves.begin(), attack_moves.end());
            }
            if (field.fld[y][x]==queen_mark){
                {
                    std::vector<step_t> attack_moves = opponents_near(x, y, true, player_num);
                    opponents.insert(opponents.end(), attack_moves.begin(), attack_moves.end());
                }
            }
        }
    }

    if (!opponents.empty()) {
        if (try_attack(step, player_num)) {
            return {true, !opponents_near(step.to_x - 1, step.to_y - 1, step.queen, player_num).empty()};
        } else {
            field.fld[opponents[0].from_y - 1][opponents[0].from_x - 1] = '.';
            return {true};
        }
    }

    if ((abs(step.from_x - step.to_x) == 1) && ((step.to_y - step.from_y == -1) && player_num == 0 ||
                                                (step.to_y - step.from_y == 1) && player_num == 1)) {

        if (to_cell != '.' ||
            (from_cell != field.player1_mark && from_cell != field.player1_queen_mark && player_num == 0) ||
            (from_cell != field.player2_mark && from_cell != field.player2_queen_mark && player_num == 1)) {
            return {false};
        }


        if (player_num == 0) {
            if (step.queen || step.to_y == 0) {
                to_cell = field.player1_queen_mark;
            } else {
                to_cell = field.player1_mark;
            }
        } else {
            if (step.queen || step.to_y == 7) {
                to_cell = field.player2_queen_mark;
            } else {
                to_cell = field.player2_mark;
            }
        }
        from_cell = '.';
        return {true};
    } else {
        if (step.queen && (abs(step.to_x - step.from_x) == abs(step.from_y - step.to_y))) {
            if (player_num == 0) {
                to_cell = field.player1_queen_mark;
            } else {
                to_cell = field.player2_queen_mark;
            }
            from_cell = '.';
            return {true};
        }
    }
    return {false};
}

bool checker_game::try_attack(const step_t &step, size_t player_num) {
    if (!step.queen && abs(step.from_x - step.to_x) == 2 && abs(step.from_y - step.to_y) == 2 ||
        (step.queen && (abs(step.to_x - step.from_x) == abs(step.from_y - step.to_y)))) {

        char &to_cell = field.fld[step.to_y - 1][step.to_x - 1];
        char &from_cell = field.fld[step.from_y - 1][step.from_x - 1];

        if (to_cell != '.') {
            return false;
        }

        std::pair<int, int> opponent_coordinates;

        if (step.to_y - step.from_y > 0) opponent_coordinates.first = step.to_y - 1;
        else opponent_coordinates.first = step.to_y + 1;

        if (step.to_x - step.from_x > 0) opponent_coordinates.second = step.to_x - 1;
        else opponent_coordinates.second = step.to_x + 1;

        char &opponent = field.fld[opponent_coordinates.first - 1][opponent_coordinates.second - 1];

        if ((player_num == 0 && (opponent == field.player2_queen_mark || opponent == field.player2_mark)) ||
            (player_num == 1 && (opponent == field.player1_queen_mark || opponent == field.player1_mark))) {

            if (player_num == 0) {
                if (step.queen || step.to_y == 1) {
                    to_cell = field.player1_queen_mark;
                } else {
                    to_cell = field.player1_mark;
                }
            } else {
                if (step.queen || step.to_y == 8) {
                    to_cell = field.player2_queen_mark;
                } else {
                    to_cell = field.player2_mark;
                }
            }

            from_cell = '.';
            opponent = '.';

            return true;
        }
    }
    return false;
}

//есть ли рядом шашка противника которую можно побить
std::vector<step_t> checker_game::opponents_near(int x, int y, bool queen, size_t player_num) {
    std::vector<step_t> opponents;

    char opponent_mark;
    char opponent_queen_mark;

    if (player_num == 0) {
        opponent_mark = field.player2_mark;
        opponent_queen_mark = field.player2_queen_mark;
    } else {
        opponent_mark = field.player1_mark;
        opponent_queen_mark = field.player2_queen_mark;
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
                opponents.emplace_back(x + 1, y + 1,  x - i, y - i);
                ul = true;
            }
            if (!ur && y - i - 1 >= 0 && x + i + 1 <= 7 && field.fld[y - i - 1][x + i + 1] == '.' &&
                (field.fld[y - i][x + i] == opponent_mark || field.fld[y - i][x + i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1, x + i + 2, y - i);
                ur = true;
            }
            if (!dl && y + i + 1 <= 7 && x - i - 1 >= 0 && field.fld[y + i + 1][x - i - 1] == '.' &&
                (field.fld[y + i][x - i] == opponent_mark || field.fld[y + i][x - i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1,  x - i, y + i + 2);
                dl = true;
            }
            if (!dr && y + i + 1 <= 7 && x + i + 1 <= 7 && field.fld[y + i + 1][x + i + 1] == '.' &&
                (field.fld[y + i][x + i] == opponent_mark || field.fld[y + i][x + i] == opponent_queen_mark)) {
                opponents.emplace_back(x + 1, y + 1,  x + i + 2, y + i + 2);
                dr = true;
            }
        }
    }
    return opponents;
}

bool checker_game::is_win_line(int x, size_t player_num) const {
    return (field.fld[x].find(field.player2_mark) == std::string::npos &&
            field.fld[x].find(field.player2_queen_mark) == std::string::npos &&
            player_num == 0) ||
           (field.fld[x].find(field.player1_mark) == std::string::npos &&
            field.fld[x].find(field.player1_queen_mark) == std::string::npos &&
            player_num == 1);
}

checker_game::game_outcome_t checker_game::is_win(size_t player_num) const {
    for (int i = 0; i < 8; i++) {
        if (!is_win_line(i, player_num))
            return IN_PROGRESS;
    }
    if (turns > 1000)
        return DRAW;
    return WIN;
}

void checker_game::play() {
    size_t counter = 1;
    bool surrender = false;

    while (is_win(counter) == IN_PROGRESS && !surrender) {
        turns++;
        counter = (counter + 1) % 2;
        bool is_correct = false;
        bool priveleged = false;
        while (!is_correct || priveleged) {
            step_t step = players[counter]->make_step(field, counter);
            if (step.from_x == -228) {
                surrender = true;
                break;
            }
            response_t result = apply_step(step, counter);
            is_correct = result.status;
            priveleged = result.priveleged;
            if (!is_correct) {
                players[counter]->on_incorrect_step(step, field);
            }
        }
    }

    //если игроку некуда пойти, он проиграл
    if (surrender) {
        for (size_t i = 0; i < players.size(); ++i) {
            if (i == counter) {
                players[i]->on_lose();
            } else {
                players[i]->on_win();
            }
        }
        return;
    }

    if (is_win(counter) == DRAW) {
        for (const auto &p : players) {
            p->on_draw();
        }
        return;
    }

    for (size_t i = 0; i < players.size(); ++i) {
        if (i == counter) {
            players[i]->on_win();
        } else {
            players[i]->on_lose();
        }
    }
}
