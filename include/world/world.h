#pragma once

#include <dachLib.h>
#include <tile.h>

class World
{
private:

public:
    array_2D<Tile> grid;
    int xSize;
    int ySize;
    int tileSize;
    
    void init(int x, int y, int tileSize){
        grid.setSize(x, y);
        xSize = x;
        ySize = y;
        this->tileSize = tileSize;
    }
};