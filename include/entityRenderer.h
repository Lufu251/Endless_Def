#pragma once

#include <SFML/Graphics.hpp>

#include <renderable.h>
#include <player.h>
#include <dataLoader.h>
#include <textureEnum.h>

class EntityRenderer
{
private:

public:

    void render(Renderable* b, sf::RenderWindow &pWindow, std::vector<sf::Texture>& textures){
        sf::Sprite sprite;
        Player* p;
        p = dynamic_cast<Player*>(b);

        switch(b->get_type()){
            case PLAYER:
                sprite.setPosition(p->position.x, p->position.y);
                sprite.setColor(sf::Color(255,255,255,255));
                sprite.setTexture(textures[playerT]);
            break;
        }

        pWindow.draw(sprite);
    }
};