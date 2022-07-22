#pragma once

#include <tile.h>
#include <dachlib.h>
#include <Eigen/Core>

class World
{
private:
    int tileSize;
    
    array_2D<Tile> grid;
public:
    Eigen::Vector2i beacorePosition;

    void resize(int x, int y){
        grid.resize(x, y);
    }

    void setTileSize(int size){
        tileSize = size;
    }

    int getTileSize(){
        return tileSize;
    }
    int sizeX(){
        return grid.getSizeX();
    }

    int sizeY(){
        return grid.getSizeY();
    }

    Tile& operator()(int x, int y){
        return grid(x, y);
    }

    const Tile& operator()(int x, int y) const {
        return grid(x, y);
    }
};