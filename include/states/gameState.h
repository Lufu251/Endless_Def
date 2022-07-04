#pragma once
#include <vector>

#include <renderable.h>
#include <player.h>
#include <entityRenderer.h>
#include <textureLoader.h>
#include <inputHandler.h>


class GameState
{
private:
    /* data */
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &pWindow) = 0;
};


