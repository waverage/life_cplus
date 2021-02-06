#include <iostream>
#include <string>
#include <sstream>
#include "Game.h"
#include <time.h>

using namespace std;

#undef main
int main(int argc, char* argv[])
{
    /* initialize random seed: */
    srand(time(NULL));

    Game game;

    game.loop();

    cout << "End of programm" << endl;

    return EXIT_SUCCESS;
}