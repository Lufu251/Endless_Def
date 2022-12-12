#define _USE_MATH_DEFINES
#include <iostream>
#include <SFML/System.hpp>
#include <Shlwapi.h>
#include <filesystem>
#include <cmath>

#include <game.h>

int main()
{
    // create new game instance
    Game game;

    game.init(1500,900,"ENDLESS_DEF");

    // run the program as long as the window is open
    while (game.Running())
    {

        //handle game events
        game.handleEvents();

        //the game main loop
        game.update();

        // the games render loop
        game.render();
    }

    return 0;
}