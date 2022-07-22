#pragma once

#include <renderable.h>
#include <entity.h>

class Player : public Entity
{
private:
public:
    Player(){}
    Player(float x, float y, int sizeX, int sizeY): Entity(x,y,sizeX,sizeY){}
    
    type get_type(){
        return PLAYER;
    }
};