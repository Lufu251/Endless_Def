#pragma once

#include <entityEnum.h>

class Renderable
{
private:
    /* data */
public:
    Renderable(){
    }
    virtual ~Renderable(){}


    virtual type get_type(){
        return RENDERABLE;
    }
};