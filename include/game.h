#include <SFML/Graphics.hpp>
#include <player.h>
#include <inputHandler.h>
#include <iostream>

class Game
{
private:
    InputHandler InputHandler;
public:
    Game(/* args */){

    }
    ~Game(){

    }


    void initialise(){
    }

    void update(sf::Time _elapsed){
        float delta_time = _elapsed.asMilliseconds();
        std::cout << delta_time << " ms\n";
        InputHandler.update();



        // reset key states on last call of game update
        InputHandler.updateKeyState();
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
