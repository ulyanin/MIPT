#include <iostream>
#include <string>
#include "life_game.h"

int main(int argc, char ** argv)
{
    srand(time(NULL));
    std::string mode = "VISUAL";  // VISUAL || SPEED_TEST
    int fieldSize = 20;
    if (argc > 1) {
        fieldSize = std::stoi(argv[1]);
    }
    if (argc > 2) {
        mode = argv[2];
    }
    std::cout << "using <fieldSize> = " << fieldSize << std::endl;
    std::cout << "using <mode> = " << mode << std::endl;
    usleep(2000000);
    do_life_game(fieldSize, mode);
    return 0;
}
