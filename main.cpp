#include <memory>

#include "game/checker_game.h"
#include "strategies/human.h"
#include "strategies/computer1.h"
#include "strategies/computer2.h"


int main() {
    /*auto player1 = std::make_shared<computer_strategy_t>("First player");
    auto player2 = std::make_shared<random_strategy_t>("Second player");

    for (int i = 0; i < 100000; ++i) {
      checker_game game(player1, player2);
      game.play();
    }

    player1->print_stat();
    player2->print_stat();*/

    auto player2 = std::make_shared<computer_strategy_t>("First player");
    auto player1 = std::make_shared<human_strategy_t>();

    checker_game game(player1, player2);
    game.play();

    return 0;
}
