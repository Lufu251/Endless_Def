#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <playing.h>



class Game
{
private:
    bool running = true;
    // create clock for time measurement between frames
    sf::Clock clock;

public:
    sf::RenderWindow window;
    InputHandler inputHandler;
    Playing playing;

    Game(){}


    bool Running() { return running;}

    // ---------------------------- init ----------------------------
    void init(int width, int height, const char* titel){
        // create window
        window.create(sf::VideoMode(width, height), titel);

        playing.init();
        window.setFramerateLimit(60);
    }


    // ---------------------------- handleEvents ----------------------------
    void handleEvents(){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
                running = false;
                std::cout << "window closed";
            }
        }
    }


    // ---------------------------- update ----------------------------
    void update(){
        // restart clock and calculate time as seconds from last update call
        float delta_time = clock.restart().asSeconds();
        // check for key input
        inputHandler.update();





        // reset key states on last call of game update
        inputHandler.updateKeyState();
    }


    // ---------------------------- render ----------------------------
    void render(){
        playing.draw(window);
    }
};