#pragma once

#include <tile.h>

class World
{
private:
    int xSize;
    int ySize;
        int tileSize;
    std::vector<Tile> grid;
public:

    void resize(int x, int y){
        grid.resize(x*y);
        xSize = x;
        ySize = y;
    }

    void setTileSize(int size){
        tileSize = size;
    }

    int getTileSize(){
        return tileSize;
    }
    int sizeX(){
        return xSize;
    }

    int sizeY(){
        return ySize;
    }

    Tile& operator()(size_t x, size_t y){
        return grid[xSize * y + x];
    }

    const Tile& operator()(size_t x, size_t y) const {
        return grid[xSize * y + x];
    }
};