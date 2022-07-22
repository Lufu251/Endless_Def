#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <inputHandler.h>
#include <playState.h>
#include <worldEditor.h>


class Game
{
private:
    // game still running
    bool running = true;
    // create clock for time measurement between frames
    sf::Clock clock;
    // all gameStates
    std::vector<std::unique_ptr<GameState>> states;

public:
    sf::RenderWindow window;
    InputHandler inputHandler;

    Game(){}


    bool Running() { return running;}

    // ---------------------------- init ----------------------------
    void init(int width, int height, const char* titel){
        // create window
        window.create(sf::VideoMode(width, height), titel);
        window.setFramerateLimit(60);
        //pushBack(std::make_unique<WorldEditor>(window));
        pushBack(std::make_unique<PlayState>(window));
    }


    // ---------------------------- handleEvents ----------------------------
    void handleEvents(){
        states.back()->handleEvents(running);
    }


    // ---------------------------- update ----------------------------
    void update(){
        // restart clock and calculate time as seconds from last update call
        float deltaTime = clock.restart().asSeconds();
        // check for key input
        inputHandler.update();

        // update the last GameState object
        states.back()->update(inputHandler, deltaTime);


        // reset key states on last call of game update
        inputHandler.updateKeyState();
    }


    // ---------------------------- render ----------------------------
    void render(){
        // draw the last GameState object
        states.back()->draw();
    }


    void changeState(std::unique_ptr<GameState>&& state){
        // delete the last element
        if(!states.empty()){
            states.pop_back();
        }

        // insert new state at the end
        states.push_back(std::move(state));
        states.back()->init();
    }

    void pushBack(std::unique_ptr<GameState>&& state){
        // insert new state at the end
        states.push_back(std::move(state));
        states.back()->init();
    }

    void popState(){
        if(!states.empty()){
            states.pop_back();
        }
    }

    void generateWorld(){
        //world
    }
};

