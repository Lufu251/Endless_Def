#pragma once

#include <SFML/Graphics.hpp>

#include <renderable.h>
#include <player.h>
#include <enemy.h>
#include <textureEnum.h>
#include <camera.h>

class EntityRenderer
{
private:

public:

    EntityRenderer(){}

    void render(std::vector<Renderable*> pRenderables, sf::RenderWindow &pWindow, std::vector<sf::Texture>& textures){
        
        sf::Sprite sprite;
        Player* p;
        Enemy* e;

        for(int i=0; i<pRenderables.size(); i++){
            Renderable* b = pRenderables[i];
            
            switch(b->get_type()){
                case PLAYER:
                    p = dynamic_cast<Player*>(b);
                    sprite.setPosition(p->position.x, p->position.y);
                    sprite.setColor(sf::Color(255,255,255,255));
                    sprite.setTexture(textures[playerT]);
                break;

                case ENEMY:
                    e = dynamic_cast<Enemy*>(b);

                    sprite.setPosition(e->position.x, e->position.y);
                    sprite.setColor(sf::Color(255,255,255,255));
                    sprite.setTexture(textures[enemyT]);
                break;
            }
        pWindow.draw(sprite);
        }
    }
};