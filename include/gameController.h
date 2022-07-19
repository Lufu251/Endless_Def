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

    void setPlayerDirection(Player &rPlayer, InputHandler &pInputHandler, float &pDeltaTime){
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;
            if(pInputHandler.key_W){
                up = 1;
            }
            if(pInputHandler.key_S){
                down = 1;
            }
            if(pInputHandler.key_A){
                left = 1;
            }
            if(pInputHandler.key_D){
                right = 1;
            }
        Eigen::Vector2f direction(static_cast<float>(right - left), static_cast<float>(down - up));
        direction.normalize();
        direction = direction * 200.f;
        direction = direction * pDeltaTime;
        
        rPlayer.setDirection(direction);
    }
};