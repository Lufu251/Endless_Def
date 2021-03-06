#pragma once

#include <renderable.h>

class Component : public Renderable
{
public:
    Eigen::Vector2f direction;
    float range;

    Component(){}
    Component(float x, float y, int sizeX, int sizeY) : Renderable(x,y,sizeX,sizeY){}
    virtual ~Component(){}

    void setPosition(int x, int y){
        position =  Eigen::Vector2f((float)x,(float)y);
        
    }

    void move(){
        position += direction;
    }

    void setDirection(Eigen::Vector2f pDirection){
        direction = pDirection;
    }
    Eigen::Vector2i getPositionRounded(){
        return position.cast<int>();
    }
};