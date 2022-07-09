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
        for (int x = 0; x < pWorld.xSize; x++){
            for (int y = 0; y < pWorld.ySize; y++){
                
                switch (pWorld.grid(x,y).getType())
                {
                    case Ground:
                        float scaleX = static_cast<float>(pWorld.tileSize) / static_cast<float>(pTextures[groundT].getSize().x);
                        float scaleY = static_cast<float>(pWorld.tileSize) / static_cast<float>(pTextures[groundT].getSize().y);
                        sprite.setPosition(static_cast<float>(x) * pWorld.tileSize, static_cast<float>(y) * pWorld.tileSize);
                        sprite.setColor(sf::Color(255,255,255,255));
                        sprite.setScale(scaleX, scaleY);
                        sprite.setTexture(pTextures[groundT]);
                    break;
                }
            pWindow.draw(sprite);
            }
        }
    }
};