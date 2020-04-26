#include "onGame.hpp"
#include <iostream>

int main(int , char * argv[]) {
    Game game;

    while (game.tick());

    return 0;
}
