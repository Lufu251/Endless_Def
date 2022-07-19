#pragma once

#include <renderable.h>

class Component
{
private:
public:
    Eigen::Vector2f position;
    Eigen::Vector2f direction;

    Component(){}
    Component(float x, float y) : position(x,y){}
    virtual ~Component();

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