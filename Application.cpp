#include "Game.hpp"
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Game game(800, 600);
    game.run();

    return 0;
}
