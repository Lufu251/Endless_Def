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
                case ENEMY:
                    e = dynamic_cast<Enemy*>(b);
                    sprite = sf::Sprite();

                    sprite.setPosition(static_cast<float>(e->getPositionRounded().x()), static_cast<float>(e->getPositionRounded().y()));
                    sprite.setColor(sf::Color(255,255,100,255));
                    sprite.setScale(2, 2);
                    sprite.setTexture(textures[enemyT]);
                break;
                case PLAYER:
                    p = dynamic_cast<Player*>(b);
                    sprite = sf::Sprite();

                    sprite.setPosition(static_cast<float>(p->getPositionRounded().x() -32), static_cast<float>(p->getPositionRounded().y() -32));
                    sprite.setColor(sf::Color(255,255,100,255));
                    sprite.setScale(2, 2);
                    sprite.setTexture(textures[playerT]);
                break;
            }
        pWindow.draw(sprite);
        }
    }
};