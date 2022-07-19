#pragma once

#include <renderable.h>
#include <entity.h>

class Player : public Entity
{
private:
public:
    Player(){}
    Player(float x, float y): Entity(x,y){}
    
    type get_type(){
        return PLAYER;
    }
};