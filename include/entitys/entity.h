#pragma once

#include <Eigen/Core>

class Entity : public Renderable
{
public:
    Eigen::Vector2f direction;

    Entity(){}
    Entity(float x, float y) : Renderable(x,y){}
    virtual ~Entity(){}


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