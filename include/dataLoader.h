#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>

#include <pathSearcher.h>

class DataLoader
{
private:
    PathSearcher pS;
    std::filesystem::path path;

public:
    
    DataLoader(){}
    ~DataLoader(){}


    void setDirectory(std::string name, int depth){
        path = pS.getDirPath(name, depth);
    }
    
    sf::Texture loadTexture(std::string fileName){
        sf::Texture texture;
        if (!texture.loadFromFile(path.string() + "/" + fileName)){std::cout << fileName << " could not load \n";}
        return texture;
    }
};