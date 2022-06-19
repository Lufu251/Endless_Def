#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <dataHandler.h>
#include <inputHandler.h>

class Game
{
private:
    InputHandler inputHandler;
    DataHandler dataHandler;

public:
    Game(){}
    ~Game(){}

    // -------------- init --------------
    void initialise(){
        dataHandler.loadTextures();
    }

    // -------------- update --------------
    void update(sf::Time pElapsed){
        float delta_time = pElapsed.asSeconds();
        inputHandler.update();
        





        // reset key states on last call of game update
        inputHandler.updateKeyState();
    }


    // -------------- render --------------
    void render(sf::RenderWindow &pWindow){
        // clear the window with black color
        pWindow.clear(sf::Color::Black);

        // draw everything here...
        //_window.draw(sprite);

        // end the current frame
        pWindow.display();
    }
};