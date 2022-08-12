#pragma once

#include <SFML/System.hpp>
#include <iostream>
#include <unordered_map>
#include <Eigen/Core>



struct key
{
    sf::Keyboard::Key type;
    bool lastFrame = false;
    bool pressed = false, pressedOnce = false;

    key(){}
    key(sf::Keyboard::Key keyboardKey): type(keyboardKey){}

    void checkPressed(){
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Keyboard::isKeyPressed(type) && lastFrame == false)
        {   
            // once when key pressed
            pressedOnce = true;
            pressed = true;
        }
    }

    void checkReleased(){
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Keyboard::isKeyPressed(type) && lastFrame == true)
        {
            // once when key released
            pressed = false;
        }
    }

    void updateState(){
        // current state to last key state from next frame
        lastFrame = pressed;

        // reset once_Key state
        pressedOnce = false;

    }
};

struct mButton
{
    sf::Mouse::Button type;
    bool lastFrame = false;
    bool pressed = false, pressedOnce = false;

    mButton(){}
    mButton(sf::Mouse::Button mouseButton): type(mouseButton){}

    void checkPressed(){
        // check if key is pressed and only set true if key was not pressed last frame
        if (sf::Mouse::isButtonPressed(type) && lastFrame == false)
        {   
            // once when key pressed
            pressedOnce = true;
            pressed = true;
        }
    }

    void checkReleased(){
        // check if key is not pressed and only set false if key was pressed last frame
        if (!sf::Mouse::isButtonPressed(type) && lastFrame == true)
        {
            // once when key released
            pressed = false;
        }
    }

    void updateState(){
        // current state to last key state from next frame
        lastFrame = pressed;

        // reset once_Key state
        pressedOnce = false;

    }
};


class InputHandler
{
    std::unordered_map<std::string, key> keys;
    std::unordered_map<std::string, mButton> mButtons;

    Eigen::Vector2i mousePosition;

    public:
    InputHandler(/* args */){}
    ~InputHandler(){}


    void update(sf::RenderWindow &pWindow){
        // iterate all keys
        for (auto& [key, value]: keys) {
            // Do stuff
            value.checkPressed();
            value.checkReleased();
        }

        for (auto& [key, value]: mButtons) {
            // Do stuff
            value.checkPressed();
            value.checkReleased();
        }

        updateMousePosition(pWindow);
    }

    

    // update the key states
    void updateState(){
        for (auto& [key, value]: keys) {
            // Do stuff
            value.updateState();
        }

        for (auto& [key, value]: mButtons) {
            // Do stuff
            value.updateState();
        }
        
    }
    bool isMousePressed(std::string name){
        return mButtons[name].pressed;
    }

    bool isMousePressedOnce(std::string name){
        return mButtons[name].pressedOnce;
    }

    bool isKeyPressed(std::string name){
        return keys[name].pressed;
    }

    bool isKeyPressedOnce(std::string name){
        return keys[name].pressedOnce;
    }

    void newKeyboardKey(std::string name, sf::Keyboard::Key type){
        keys.insert(std::make_pair(name, key(type)));
    }
    void newMouseButton(std::string name, sf::Mouse::Button type){
        mButtons.insert(std::make_pair(name, mButton(type)));
    }

    void updateMousePosition(sf::RenderWindow &pWindow){
        sf::Vector2i mP = sf::Mouse::getPosition(pWindow);
        mousePosition.x() = mP.x;
        mousePosition.y() = mP.y;
    }
    Eigen::Vector2i getMousePosition(sf::RenderWindow &pWindow){
        return Eigen::Vector2i(mousePosition.x(), mousePosition.y());
    }
};
 