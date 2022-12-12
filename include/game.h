#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <inputHandler.h>
#include <StateHandler.h>
#include <playState.h>
#include <worldEditor.h>
#include <menuState.h>

StateHandler stateHandler;

class Game
{
private:
    // game still running
    bool running = true;
    // create clock for time measurement between frames
    sf::Clock clock;

public:
    sf::RenderWindow window;

    Game(){}


    bool Running() { return running;}

    // ---------------------------- init ----------------------------
    void init(int width, int height, const char* titel){
        // create window
        window.create(sf::VideoMode(width, height), titel);
        window.setFramerateLimit(120);
        stateHandler.pushBack(std::make_unique<PlayState>(window));
    }


    // ---------------------------- handleEvents ----------------------------
    void handleEvents(){
        stateHandler.states.back()->handleEvents(running);
    }


    // ---------------------------- update ----------------------------
    void update(){
        // restart clock and calculate time as seconds from last update call
        float deltaTime = clock.restart().asSeconds();

        // update the last GameState object
        stateHandler.states.back()->update(deltaTime);
    }


    // ---------------------------- render ----------------------------
    void render(){
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw the last GameState object
        stateHandler.states.back()->draw();

        // render all drawn objects
        window.display();
    }
};

