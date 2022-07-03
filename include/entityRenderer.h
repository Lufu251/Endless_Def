#pragma once

#include <SFML/Graphics.hpp>

#include <renderable.h>
#include <player.h>

class EntityRenderer
{
private:
    TextureLoader& textureLoader;
public:
    EntityRenderer(TextureLoader& tL):textureLoader(tL){}
    ~EntityRenderer(){}
    
    void render(Renderable* b, sf::RenderWindow &pWindow){
        sf::Sprite sprite;
        Player* p;
        p = dynamic_cast<Player*>(b);

        switch(b->get_type()){
            case PLAYER:
                sprite.setPosition(p->position.x, p->position.y);
                sprite.setColor(sf::Color(255,255,255,255));
                sprite.setTexture(textureLoader.tPlayer);
            break;
        }

        pWindow.draw(sprite);
    }
};