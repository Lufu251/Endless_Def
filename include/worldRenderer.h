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

        int xStartPosition = static_cast<int>((1 + pCamera.getOffset().x() - static_cast<int>(pWindow.getSize().x) / 2.f) / pWorld.getTileSize() -2);
        int yStartPosition = static_cast<int>((1 + pCamera.getOffset().y() - static_cast<int>(pWindow.getSize().y) / 2.f) / pWorld.getTileSize() -2);
        
        int xEndPosition = xStartPosition + xSize;
        int yEndPosition = yStartPosition + ySize;

        if(xStartPosition < 0){
            xStartPosition = 0;
        }
        if(yStartPosition < 0){
            yStartPosition = 1;
        }
        if(xEndPosition > pWorld.sizeX()){
            xEndPosition = pWorld.sizeX();
        }
        if(yEndPosition > pWorld.sizeY()){
            yEndPosition = pWorld.sizeY();
        }
        std::cout << "xS: " << xStartPosition << " yS: " << yStartPosition << " xE: " << xEndPosition << " yE: " << yEndPosition << "\n";
        // loop visible area
        for (int x = xStartPosition; x < xEndPosition; x++){
            for (int y = yStartPosition; y < yEndPosition; y++){
                int textureSize = 16;
                float scaleX = static_cast<float>(pWorld.getTileSize()) / textureSize;
                float scaleY = static_cast<float>(pWorld.getTileSize()) / textureSize;

                    switch (pWorld(x,y).getType())
                    {
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
                        case Borium:
                            sprite.setPosition(static_cast<float>(x) * pWorld.getTileSize(), static_cast<float>(y) * pWorld.getTileSize());
                            sprite.setColor(sf::Color(255,255,255,255));
                            sprite.setScale(scaleX, scaleY);
                            sprite.setTexture(pTextures[boriumT]);
                        break;
                        case Beacore:
                            sprite.setPosition(static_cast<float>(x) * pWorld.getTileSize(), static_cast<float>(y) * pWorld.getTileSize());
                            sprite.setColor(sf::Color(255,255,255,255));
                            sprite.setScale(scaleX, scaleY);
                            sprite.setTexture(pTextures[beacoreT]);
                        break;
                        case Spawner:
                            sprite.setPosition(static_cast<float>(x) * pWorld.getTileSize(), static_cast<float>(y) * pWorld.getTileSize());
                            sprite.setColor(sf::Color(255,255,255,255));
                            sprite.setScale(scaleX, scaleY);
                            sprite.setTexture(pTextures[spawnerT]);
                        break;
                    }
                pWindow.draw(sprite);
            }
        }
    }
};