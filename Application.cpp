#include "Game.hpp"
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Game game(1000, 800);
    game.run();

    return 0;
}
