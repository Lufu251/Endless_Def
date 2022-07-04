#pragma once
#include <renderable.h>
#include <gameState.h>

class Player : public Renderable
{
private:

public:
    sf::Vector2f position;
    Player(){}
    
    void init(int x, int y){
        position =  sf::Vector2f((float)x,(float)y);
        
    }

    type get_type(){
        return PLAYER;
    }

};