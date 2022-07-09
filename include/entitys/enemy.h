#pragma once

#include <renderable.h>

class Enemy : public Renderable
{
private:
    
public:
    sf::Vector2f position;
    Enemy(){}

    type get_type(){
        return ENEMY;
    }

    void init(int x, int y){
        position =  sf::Vector2f((float)x,(float)y);
        
    }

    void move(sf::Vector2f move){
        position += move;
    }
};