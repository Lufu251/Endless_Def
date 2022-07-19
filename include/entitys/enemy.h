#pragma once

#include <entity.h>

class Enemy : public Entity
{
private:
    
public:
    Enemy(){}
    Enemy(float x, float y): Entity(x,y){}

    type get_type(){
        return ENEMY;
    }
};