#include <iostream>
#include <SFML/System.hpp>
#include <Shlwapi.h>
#include <filesystem>

#include <game.h>
#include <pathSearcher.h>

int main()
{
    // create new game instance
    Game game;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Clock clock;
    
    window.setFramerateLimit(60);

    game.initialise();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // restart clock and get elapsed time
        sf::Time elapsed = clock.restart();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //the game main loop
        game.update(elapsed);

        // the games render loop
        game.render(window);

    }

    return 0;
}