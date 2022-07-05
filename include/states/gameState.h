#pragma once

class GameState
{
private:
    /* data */
public:

    virtual ~GameState() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &pWindow) = 0;
};