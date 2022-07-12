#pragma once

class Tile
{
private:
    int type = 0;
public:
    Tile(){}

    int& getType(){
        return type;
    }

    void changeType(int t){
        type = t;
    }
};
