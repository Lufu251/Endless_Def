#pragma once

#include <entity.h>

class Enemy : public Entity
{
public:
    Enemy(){}
    Enemy(float x, float y, int sizeX, int sizeY): Entity(x,y,sizeX,sizeY){}

    type get_type(){
        return ENEMY;
    }
};