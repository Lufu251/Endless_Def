#pragma once

#include <inputHandler.h>
#include <player.h>
#include <Eigen/Core>

class GameController
{
private:
    /* data */
public:
    GameController(){}
    ~GameController(){}

    void setPlayerDirection(std::vector<std::unique_ptr<Entity>> &rEntitys, InputHandler &pInputHandler, float &pDeltaTime){
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;
            if(pInputHandler.isKeyPressed("key_W")){
                up = 1;
            }
            if(pInputHandler.isKeyPressed("key_S")){
                down = 1;
            }
            if(pInputHandler.isKeyPressed("key_A")){
                left = 1;
            }
            if(pInputHandler.isKeyPressed("key_D")){
                right = 1;
            }
            
        Eigen::Vector2f direction(static_cast<float>(right - left), static_cast<float>(down - up));
        direction.normalize();
        direction = direction * 200.f;
        direction = direction * pDeltaTime;
        
        rEntitys[0]->setDirection(direction);
    }

    void worldBorderConstrain(World &rWorld, std::vector<std::unique_ptr<Entity>> &rEntitys){
        for(int i=0; i < rEntitys.size(); i++){
            if(rEntitys[i]->position.x() < 0){
                rEntitys[i]->setXPosition(0);
            }
            else if(rEntitys[i]->position.x() > rWorld.sizeX() * rWorld.getTileSize() - rEntitys[i]->size.x()){
                rEntitys[i]->setXPosition((float)rWorld.sizeX() * rWorld.getTileSize() - rEntitys[i]->size.x());
            }
            if(rEntitys[i]->position.y() < 0){
                rEntitys[i]->setYPosition(0);
            }
            else if(rEntitys[i]->position.y() > rWorld.sizeY() * rWorld.getTileSize() - rEntitys[i]->size.y()){
                rEntitys[i]->setYPosition((float)rWorld.sizeY() * rWorld.getTileSize() - rEntitys[i]->size.y());
            }
        }
    }

    void worldCollision(World &rWorld, std::vector<std::unique_ptr<Entity>> &rEntitys){
        for(int i=0; i < rEntitys.size(); i++){
            // get player position on the grid
            int gridX = static_cast<int>(rEntitys[i]->position.x() / rWorld.getTileSize());
            int gridY = static_cast<int>(rEntitys[i]->position.y() / rWorld.getTileSize());
            // calculate amount of grid tiles to check depending on the size of the entity
            int jX = static_cast<int>(rEntitys[i]->size.x() / rWorld.getTileSize() +2);
            int kY = static_cast<int>(rEntitys[i]->size.y() / rWorld.getTileSize() +2);
            for(int j=0; j < jX; j++){
                for(int k=0; k < kY; k++){
                    int gridPX = gridX + j;
                    int gridPY = gridY + k;

                    // the checked gridPosition can't be larger or smaller than world size
                    gridPX = std::clamp(gridPX, 0, rWorld.sizeX()-1);
                    gridPY = std::clamp(gridPY, 0, rWorld.sizeY()-1);
                    if(rWorld(gridPX, gridPY).blocking == 0){
                        // no collision
                    }
                    // collision
                    else if( rEntitys[i]->position.x() < gridPX * rWorld.getTileSize() + rWorld.getTileSize() &&
                        rEntitys[i]->position.x() + rEntitys[i]->size.x() > gridPX * rWorld.getTileSize() &&
                        rEntitys[i]->position.y() < gridPY * rWorld.getTileSize() + rWorld.getTileSize() &&
                        rEntitys[i]->size.y() + rEntitys[i]->position.y() > gridPY * rWorld.getTileSize()){
                        
                        float xDiv1 = rEntitys[i]->position.x() - (gridPX +1) * rWorld.getTileSize();
                        float xDiv2 = rEntitys[i]->position.x() + rEntitys[i]->size.x() - gridPX * rWorld.getTileSize();
                        float yDiv1 = rEntitys[i]->position.y() - (gridPY +1) * rWorld.getTileSize();
                        float yDiv2 = rEntitys[i]->position.y() + rEntitys[i]->size.y() - gridPY * rWorld.getTileSize();
                        // closest edge of the coliding rectangle
                        float absX1 = std::fabsf(xDiv1);
                        float absX2 = std::fabsf(xDiv2);
                        float absY1 = std::fabsf(yDiv1);
                        float absY2 = std::fabsf(yDiv2);
                        // x1
                        if(absX1 < absX2 && absX1 < absY1 && absX1 < absY2){
                            rEntitys[i]->setXPosition(static_cast<float>(gridPX +1) * rWorld.getTileSize());
                        }
                        // x2
                        else if(absX2 < absX1 && absX2 < absY1 && absX2 < absY2){
                            rEntitys[i]->setXPosition(gridPX * rWorld.getTileSize() - rEntitys[i]->size.x());
                        }
                        // y1
                        else if(absY1 < absX2 && absY1 < absX1 && absY1 < absY2){
                            rEntitys[i]->setYPosition(static_cast<float>(gridPY +1) * rWorld.getTileSize());
                        }
                        // y2
                        else if(absY2 < absX2 && absY2 < absY1 && absY2 < absX1){
                            rEntitys[i]->setYPosition(gridPY * rWorld.getTileSize() - rEntitys[i]->size.y());
                        }
                    }
                }
            }
        }
    }
};