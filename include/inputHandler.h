#pragma once
#include <SFML/System.hpp>
#include <iostream>

class InputHandler
{
private:

// privat bool for logic reasons
bool last_Key_W = false;
bool last_Key_A = false;
bool last_Key_S = false;
bool last_Key_D = false;
bool last_Key_1 = false;
bool last_Key_2 = false;
bool last_Key_3 = false;
bool last_Key_4 = false;
bool last_Key_5 = false;

public:

// public bool to check if the key was pressed
bool key_W = false, once_Key_W = false;
bool key_A = false, once_Key_A = false;
bool key_S = false, once_Key_S = false;
bool key_D = false, once_Key_D = false;
bool key_1 = false, once_Key_1 = false;
bool key_2 = false, once_Key_2 = false;
bool key_3 = false, once_Key_3 = false;
bool key_4 = false, once_Key_4 = false;
bool key_5 = false, once_Key_5 = false;

    InputHandler(/* args */){}
    ~InputHandler(){}


    void update(){
        checkKeysPressed();
        checkKeysReleased();
    }
    
    
    void checkKeysPressed(){
        // -------------- W --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && key_W == false)
        {   
            // once when key pressed
            once_Key_W = true;
            key_W = true;
        }

        // -------------- A --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && key_A == false)
        {   
            // once when key pressed
            once_Key_A = true;
            key_A = true;
        }
        // -------------- S --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && key_S == false)
        {   
            // once when key pressed
            once_Key_S = true;
            key_S = true;
        }

        // -------------- D --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && key_D == false)
        {
            // once when key pressed
            once_Key_D = true;
            key_D = true;
        }
        // -------------- 1 --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && key_1 == false)
        {
            // once when key pressed
            once_Key_1 = true;
            key_1 = true;
        }
        // -------------- 2 --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && key_2 == false)
        {
            // once when key pressed
            once_Key_2 = true;
            key_2 = true;
        }
        // -------------- 3 --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && key_3 == false)
        {
            // once when key pressed
            once_Key_3 = true;
            key_3 = true;
        }
        // -------------- 4 --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && key_4 == false)
        {
            // once when key pressed
            once_Key_4 = true;
            key_4 = true;
        }
        // -------------- 5 --------------
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && key_5 == false)
        {
            // once when key pressed
            once_Key_5 = true;
            key_5 = true;
        }

    }

    void checkKeysReleased(){
        // -------------- W --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && last_Key_W == true)
        {
            // once when key released
            key_W = false;
        }

        // -------------- A --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && last_Key_A == true)
        {
            // once when key released
            key_A = false;
        }

        // -------------- S --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && last_Key_S == true)
        {
            // once when key released
            key_S = false;
        }

        // -------------- D --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && last_Key_D == true)
        {
            // once when key released
            key_D = false;
        }
        // -------------- 1 --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && last_Key_1 == true)
        {
            // once when key released
            key_1 = false;
        }
        // -------------- 2 --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && last_Key_2 == true)
        {
            // once when key released
            key_2 = false;
        }
        // -------------- 3 --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && last_Key_3 == true)
        {
            // once when key released
            key_3 = false;
        }
        // -------------- 4 --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && last_Key_4 == true)
        {
            // once when key released
            key_4 = false;
        }
        // -------------- 5 --------------
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && last_Key_5 == true)
        {
            // once when key released
            key_5 = false;
        }
    }
    // update the key states
    void updateKeyState(){
        // current state to last key state from next frame
        last_Key_W = key_W;
        last_Key_A = key_A;
        last_Key_S = key_S;
        last_Key_D = key_D;
        last_Key_1 = key_1;
        last_Key_2 = key_2;
        last_Key_3 = key_3;
        last_Key_4 = key_4;
        last_Key_5 = key_5;



        // reset once_Key state
        once_Key_W = false;
        once_Key_A = false;
        once_Key_S = false;
        once_Key_D = false;
        once_Key_1 = false;
        once_Key_2 = false;
        once_Key_3 = false;
        once_Key_4 = false;
        once_Key_5 = false;
    }
};
 