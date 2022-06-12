#include <SFML/Graphics.hpp>
#include <player.h>
#include <iostream>

class Game
{
private:
    /* data */
public:
    Game(/* args */){

    }
    ~Game(){

    }


    void initialise(){
        sf::Vector2f v1(5,3);
        sf::Vector2f v2 = v1 * 5.f;
        std::cout << v2.x << " " << v2.y;

    }

    void update(sf::Time _elapsed){
        float delta_time = _elapsed.asSeconds();


    }

    void render(sf::RenderWindow &_window){
        // clear the window with black color
        _window.clear(sf::Color::Black);

        // draw everything here...
        //window.draw(shape);

        // end the current frame
        _window.display();
    }
};
