#include <iostream>
#include <SFML/System.hpp>
#include <Shlwapi.h>
#include <filesystem>

#include <game.h>

int main()
{
    // create new game instance
    Game game;

    game.init(800,600,"ENDLESS_DEF");

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