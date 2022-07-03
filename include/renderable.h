#pragma once

enum type{
    RENDERABLE, PLAYER, ENEMY
};

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