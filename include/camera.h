/*
    Camera class
    consist of a sf::View and a float vector

    When creating a new Camera two functions need to be called.
    setViewport and reset
    This will set the Viewport and the View of the sf:View.

    Follow will follow the position you pass in to the function.
    Constrain will set boundaris to prevent the camera from following over the wolrd borders
    update will set the view to the current offset
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <world.h>
#include <Eigen/Core>

class Camera
{
private:
    sf::View view;
    Eigen::Vector2i offset;
public:
    Camera(){}

    void follow(float xPosition, float yPosition){
        offset.x() = static_cast<int>(xPosition);
        offset.y() = static_cast<int>(yPosition);

        view.setCenter(static_cast<float>(offset.x()), static_cast<float>(offset.y()));
    }

    void constrain(sf::Window& window, World &pWorld){
        int halfWindowX = window.getSize().x / 2;
        int halfWindowY = window.getSize().y / 2;

        // prevent shifting the tiles over the world border
        if (offset.x() > pWorld.sizeX() * pWorld.getTileSize() - halfWindowX)
        {offset.x() = pWorld.sizeX() * pWorld.getTileSize() - halfWindowX;}

        if (offset.y() > pWorld.sizeY() * pWorld.getTileSize() - halfWindowY)
        {offset.y() = pWorld.sizeY() * pWorld.getTileSize() - halfWindowY;}

        if (offset.x() < halfWindowX)
        {offset.x() = halfWindowX;}

        if (offset.y() < halfWindowY)
        {offset.y() = halfWindowY;}


    }

    void update(){
        view.setCenter(static_cast<float>(offset.x()), static_cast<float>(offset.y()));
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