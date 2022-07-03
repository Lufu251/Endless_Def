#pragma once
#include <renderable.h>

class Player : public Renderable
{
private:

public:
    sf::Vector2f position;
    Player()
    {}

    void init(int x, int y, const sf::Texture& texture){
        position.x = (float)x;
        position.y = (float)y;
        

    }
    
    type get_type(){
        return PLAYER;
    }

};