#pragma once

#include <vector>


// -------------- 2DVector --------------

template<typename T>
struct array_2D{
private:
    int x_size;
    int y_size;
    std::vector<T> data;

public:
    array_2D(){}
    array_2D(size_t x, size_t y):data(x*y), x_size(x), y_size(y){}
    
    void resize(int x, int y){
        data.resize(x * y);
        x_size = x;
        y_size = y;
    }

    int getSizeX(){
        return x_size;
    }

    int getSizeY(){
        return y_size;
    }

    T& operator()(size_t i, size_t j){
        return data[x_size * j + i];
    }

    const T& operator()(size_t i, size_t j) const {
        return data[y_size * j + i];
    }
};