#pragma once

class Tile
{
private:
    int type = 0;
public:
    int blocking = 0;
    Tile(){}

    int& getType(){
        return type;
    }

    int& getBlocking(){
        return blocking;
    }

    void changeType(int t){
        type = t;
        if(t > 0){
            blocking = 1;
        }
        else{
            blocking = 0;
        }
    }
};
