#pragma once

#include <algorithm>
#include <string>
#include <iostream>

struct step_t {
    step_t(int from_x, int from_y, int to_x, int to_y, bool queen) :
            from_x{from_x},
            from_y{from_y},
            to_x{to_x},
            to_y{to_y},
            queen{queen} {}

    step_t(int from_x, int from_y, int to_x, int to_y) :
            from_x{from_x},
            from_y{from_y},
            to_x{to_x},
            to_y{to_y},
            queen{false} {}

    int from_x, from_y, to_x, to_y;
    bool queen;
};

struct response_t {
    response_t(bool status, bool privileged) : status{status}, priveleged{privileged} {}

    response_t(bool status) : status{status}, priveleged{false} {}

    bool status;
    bool priveleged;
};

struct field_t {
    field_t() {
        fld[7] = ("w.w.w.w.");
        fld[6] = (".w.w.w.w");
        fld[5] = ("w.w.w.w.");
        fld[4] = ("........");
        fld[3] = ("........");
        fld[2] = (".b.b.b.b");
        fld[1] = ("b.b.b.b.");
        fld[0] = (".b.b.b.b");
    }

    std::string fld[8];

    const char player1_mark = 'w';
    const char player2_mark = 'b';
    const char player1_queen_mark = 'W';
    const char player2_queen_mark = 'B';

    void print_field() const {
        std::cout << std::endl;
        std::cout << "Field:" << std::endl;
        for (int y = 0; y < 8; y++) {
            std::cout << y + 1 << " ";
            for (int x = 0; x < 8; x++) {
                std::cout << fld[y][x] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "  1 2 3 4 5 6 7 8"<< std::endl;
    }

    bool is_reachable(step_t step) const {
        return is_reachable(step.from_x, step.from_y, step.to_x, step.to_y);
    }

    bool is_reachable(int from_x, int from_y, int to_x, int to_y) const {
        return !(to_x > 8 || to_y > 8 || to_x < 1 || to_y < 1 || from_x > 8 || from_y > 8 ||
                 from_x < 1 || from_y < 1);
    }
};
