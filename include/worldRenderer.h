#pragma once

#include <world.h>
#include <tileTypes.h>
#include <textureEnum.h>
#include <camera.h>

class WorldRenderer
{
private: 
public:
    WorldRenderer(){}

    void render(World &pWorld, sf::RenderWindow &pWindow, std::vector<sf::Texture>& pTextures){
        sf::Sprite sprite;
        
        // loop grid
        for (int x = 0; x < pWorld.sizeX(); x++){
            for (int y = 0; y < pWorld.sizeY(); y++){

                int textureSize = 32;
                float scaleX = static_cast<float>(pWorld.getTileSize()) / textureSize;
                float scaleY = static_cast<float>(pWorld.getTileSize()) / textureSize;

                switch (pWorld(x,y).getType())
                {
                    case Empty:
                        sprite.setPosition(static_cast<float>(x) * pWorld.getTileSize(), static_cast<float>(y) * pWorld.getTileSize());
                        sprite.setColor(sf::Color(255,255,255,255));
                        sprite.setScale(scaleX, scaleY);
                        sprite.setTexture(pTextures[emptyT]);
                    break;
                    case Grass:
                        sprite.setPosition(static_cast<float>(x) * pWorld.getTileSize(), static_cast<float>(y) * pWorld.getTileSize());
                        sprite.setColor(sf::Color(255,255,255,255));
                        sprite.setScale(scaleX, scaleY);
                        sprite.setTexture(pTextures[grassT]);
                    break;
                    case Rock:
                        sprite.setPosition(static_cast<float>(x) * pWorld.getTileSize(), static_cast<float>(y) * pWorld.getTileSize());
                        sprite.setColor(sf::Color(255,255,255,255));
                        sprite.setScale(scaleX, scaleY);
                        sprite.setTexture(pTextures[rockT]);
                    break;
                }
            pWindow.draw(sprite);
            }
        }
    }
};