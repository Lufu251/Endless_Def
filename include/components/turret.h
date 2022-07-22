#pragma once

#include <component.h>

class Turret : public Component
{
private:
    /* data */
public:
    Turret(){}
    Turret(float x, float y, int sizeX, int sizeY) : Component(x,y,sizeX,sizeY){}
};