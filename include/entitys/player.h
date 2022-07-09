#pragma once

#include <renderable.h>

class Player : public Renderable
{
private:

public:
    sf::Vector2f position;
    Player(){}
    
    type get_type(){
        return PLAYER;
    }

    void init(int x, int y){
        position =  sf::Vector2f((float)x,(float)y);
        
    }

    void move(sf::Vector2f move){
        position += move;
    }
};