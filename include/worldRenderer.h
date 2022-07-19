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

    void render(World &pWorld, sf::RenderWindow &pWindow, Camera &pCamera, std::vector<sf::Texture>& pTextures){
        sf::Sprite sprite;
        
        //calculate visible area
        int xSize = pWindow.getSize().x / pWorld.getTileSize() + 4;
        int ySize = pWindow.getSize().y / pWorld.getTileSize() + 4;
        int xStartPosition = (1 + pCamera.getOffset().x() - pWindow.getSize().x /2) / pWorld.getTileSize() -2;
        int yStartPosition = (1 + pCamera.getOffset().y() - pWindow.getSize().y/2) / pWorld.getTileSize() -2;
        int xEndPosition = xStartPosition + xSize;
        int yEndPosition = yStartPosition + ySize;
        if(xStartPosition < 0){
            xStartPosition = 0;
        }
        if(yStartPosition < 0){
            yStartPosition = 0;
        }
        if(xEndPosition > pWorld.sizeX()){
            xEndPosition = pWorld.sizeX();
        }
        if(yEndPosition > pWorld.sizeY()){
            yEndPosition = pWorld.sizeY();
        }

        // loop visible area
        for (int x = xStartPosition; x < xEndPosition; x++){
            for (int y = yStartPosition; y < yEndPosition; y++){

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