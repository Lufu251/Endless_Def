#pragma once

#include <SFML/Graphics.hpp>

#include <renderable.h>
#include <player.h>
#include <textureLoader.h>

class EntityRenderer
{
private:

public:

    void render(Renderable* b, sf::RenderWindow &pWindow, TextureLoader &tL){
        sf::Sprite sprite;
        Player* p;
        p = dynamic_cast<Player*>(b);

        switch(b->get_type()){
            case PLAYER:
                sprite.setPosition(p->position.x, p->position.y);
                sprite.setColor(sf::Color(255,255,255,255));
                sprite.setTexture(tL.tPlayer);
            break;
        }

        pWindow.draw(sprite);
    }
};