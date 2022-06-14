#include <SFML/System.hpp>
#include <iostream>

class InputHandler
{
private:

// privat bool for logic reasons
bool last_Key_A = false;

public:

// public bool to check if the key was pressed
bool key_A = false, once_Key_A = false;

    InputHandler(/* args */){
        
    }
    ~InputHandler(){

    }


    void update(){
        checkKeysPressed();
        checkKeysReleased();
    }
    
    
    void checkKeysPressed(){
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && key_A == false)
        {   
            // once when key pressed
            once_Key_A = true;
            key_A = true;
        }

    }

    void checkKeysReleased(){
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && last_Key_A == true)
        {
            // once when key released
            key_A = false;
            
        }

    }
    // update the key states
    void updateKeyState(){
        // current state to last key state from next frame
        last_Key_A = key_A;


        // reset once_Key state
        once_Key_A = false;
    }
};
 