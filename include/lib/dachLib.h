#pragma once

#include <vector>


// -------------- 2DVector --------------

template<typename T>
struct array_2D{

private:
    std::vector<T> data;
    size_t x_size;
    size_t y_size;

public:

    array_2D(){}

    void setSize(size_t x, size_t y){
        data.resize(x*y);
        x_size = x;
        y_size = y;
    }

    int sizeX(){
        return x_size;
    }
    int sizeY(){
        return y_size;
    }

    T& operator()(size_t i, size_t j){
        return data[i * j + i];
    }

    const T& operator()(size_t i, size_t j) const {
        return data[i * j + i];
    }
};

// -------------- next class --------------