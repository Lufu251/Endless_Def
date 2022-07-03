#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <textureLoader.h>
#include <inputHandler.h>
#include <gameState.h>
#include <entityRenderer.h>


class Game
{
private:

public:
    InputHandler inputHandler;
    TextureLoader textureLoader;
    GameState gameState;
    EntityRenderer entityRender;

    Game():entityRender(textureLoader){}
    ~Game(){}

    // -------------- init --------------
    void initialise(){
        textureLoader.loadTextures();
        gameState.player.init(50, 50, textureLoader.tPlayer);

        //test
        gameState.renderables.push_back(&gameState.player);

    }

    // -------------- update --------------
    void update(sf::Time pElapsed){
        float delta_time = pElapsed.asSeconds();
        // check for key input
        inputHandler.update();





        // reset key states on last call of game update
        inputHandler.updateKeyState();
    }

    // -------------- render --------------
    void render(sf::RenderWindow &pWindow){
        // clear the window with black color
        pWindow.clear(sf::Color::Black);

        // draw everything here...
        for(int i=0; i<gameState.renderables.size(); i++){
        entityRender.render(gameState.renderables[i], pWindow);
        }

        // end the current frame
        pWindow.display();
    }
};