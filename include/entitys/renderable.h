#pragma once

#include <renderableEnum.h>
#include <Eigen/Core>

class Renderable
{
public:
    Eigen::Vector2f position;
    Eigen::Vector2f size;
    Renderable(){}
    Renderable(float x, float y, int sizeX, int sizeY): position(x, y), size(sizeX, sizeY){
    }
    virtual ~Renderable(){}


    virtual type get_type(){
        return RENDERABLE;
    }
};