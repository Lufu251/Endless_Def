#pragma once

#include <entityEnum.h>
#include <Eigen/Core>

class Renderable
{
private:
    /* data */
public:
    Eigen::Vector2f position;
    Renderable(){}
    Renderable(float x, float y): position(x, y){
    }
    virtual ~Renderable(){}


    virtual type get_type(){
        return RENDERABLE;
    }
};