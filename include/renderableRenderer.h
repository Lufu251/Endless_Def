#pragma once

#include <SFML/Graphics.hpp>

#include <renderable.h>
#include <Entity.h>
#include <camera.h>

class RenderableRenderer
{
private:

public:

    RenderableRenderer(){}

    void render(std::vector<Renderable*> pRenderables, sf::RenderWindow &pWindow, DataHandler &dataHandler){
        


        for(int i=0; i<pRenderables.size(); i++){
            Renderable* b = pRenderables[i];
            float scaleX = 1;
            float scaleY = 1;
            sf::Sprite sprite;
            
            Entity* e = static_cast<Entity*>(b);
            
            switch(b->get_type()){
                case ENEMY:

                    sprite.setPosition(static_cast<float>(e->getPositionRounded().x()), static_cast<float>(e->getPositionRounded().y()));
                    
                    sprite.setColor(sf::Color(255,255,255,255));
                    sprite.setTexture(dataHandler.getTexture("enemyT"));
                    scaleX = e->size.x() / sprite.getTexture()->getSize().x;
                    scaleY = e->size.y() / sprite.getTexture()->getSize().y;
                    sprite.setScale(scaleX, scaleY);
                break;
                case PLAYER:

                    sprite.setPosition(static_cast<float>(e->getPositionRounded().x()), static_cast<float>(e->getPositionRounded().y()));
                    sprite.setColor(sf::Color(255,255,255,255));
                    sprite.setTexture(dataHandler.getTexture("playerT"));
                    scaleX = e->size.x() / sprite.getTexture()->getSize().x;
                    scaleY = e->size.y() / sprite.getTexture()->getSize().y;
                    sprite.setScale(scaleX, scaleY);
                break;
            }
        pWindow.draw(sprite);
        }
    }
};