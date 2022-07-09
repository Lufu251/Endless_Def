/*
    Camera class
    consist of a sf::View and a float vector

    When creating a new Camera two functions need to be called.
    setViewport and reset
    This will set the Viewport and the View of the sf:View.

    Follow will follow the position you pass in to the function.
    Constraint will set boundaris to prevent the camera from following over the wolrd borders
    last call update to change to view to the current location
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <world.h>

class Camera
{
private:
    sf::View view;
    sf::Vector2f offset;
public:
    Camera(){}

    void follow(float xPosition, float yPosition){
        offset.x = xPosition;
        offset.y = yPosition;
        view.setCenter(offset.x, offset.y);
    }
    void constraint(sf::Window& window, World &pWorld){
        float halfWindowX = static_cast<float>(window.getSize().x / 2);
        float halfWindowY = static_cast<float>(window.getSize().y / 2);

        // prevent shifting the tiles over the world border
        if (offset.x < halfWindowX)
        {offset.x = halfWindowX;}

        if (offset.y < halfWindowY)
        {offset.y = halfWindowY;}

        if (offset.x > pWorld.xSize * pWorld.tileSize - halfWindowX)
        {offset.x = pWorld.xSize * pWorld.tileSize - halfWindowX;}

        if (offset.y > pWorld.ySize * pWorld.tileSize - halfWindowY)
        {offset.y = pWorld.ySize * pWorld.tileSize - halfWindowY;}
    }
    void update(){
        view.setCenter(offset.x, offset.y);
    }

    void setViewport(sf::FloatRect rect){
        view.setViewport(rect);
    }
    void reset(sf::FloatRect rect){
        view.reset(rect);
    }

    sf::View& getView(){
        return view;
    }
};