#pragma once

#include <inputHandler.h>
#include <SFML/Graphics.hpp>

struct StateHandler;
class GameState
{
private:

public:
    sf::RenderWindow &window;

    GameState(sf::RenderWindow &rWindow): window(rWindow){}
    virtual ~GameState() = default;

    virtual void init() = 0;
    virtual void update(float &pDeltaTime) = 0;
    virtual void draw() = 0;
    virtual void handleEvents(bool &pRunning) = 0;
};