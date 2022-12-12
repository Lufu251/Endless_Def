#pragma once

#include <inputHandler.h>
#include <gameState.h>


class MenuState : public GameState
{
    InputHandler inputHandler;
    DataHandler dataHandler;
    buttonHandler buttonHandler;

    MenuState(sf::RenderWindow &rWindow): GameState(rWindow){}

    void init(){
        dataHandler.setSaveDirectory("data/saves", 3);
        dataHandler.setTextureDirectory("data/textures", 3);
        dataHandler.loadFont("arial.ttf");

        inputHandler.newMouseButton("left", sf::Mouse::Left);
        buttonHandler.addButton(button(200,200,100,50,"Test"), [](){});
    }

    void update(float &pDeltaTime){
        // check for key input
        inputHandler.update(window);
        
        buttonHandler.updateButtons(window, inputHandler);
        // reset key states on last call of game update
        inputHandler.updateState();
    }

    void draw(){
        buttonHandler.drawButtons(window);
    }

    void handleEvents(bool &pRunning){
        
    }
};