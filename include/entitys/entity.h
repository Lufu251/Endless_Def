#pragma once

#include <Eigen/Core>

class Entity : public Renderable
{
public:
    Eigen::Vector2f direction;

    Entity(){}
    Entity(float x, float y, int sizeX, int sizeY) : Renderable(x,y,sizeX,sizeY){}
    virtual ~Entity(){}


    void setPosition(float x, float y){
        position =  Eigen::Vector2f(x,y);
        
    }
    void setYPosition(float y){
        position.y() = y;
    }
    void setXPosition(float x){
        position.x() = x;
    }

    void move(){
        position += direction;
    }
    void move(Eigen::Vector2f nDirection){
        position += nDirection;
    }

    void setDirection(Eigen::Vector2f pDirection){
        direction = pDirection;
    }
    Eigen::Vector2i getPositionRounded(){
        return position.cast<int>();
    }
};