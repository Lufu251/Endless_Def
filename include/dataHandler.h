#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>

#include <pathSearcher.h>

class DataHandler
{
private:
    PathSearcher pS;

public:
    sf::Texture tPlayer;
    std::filesystem::path path;

    DataHandler(/* args */){}
    ~DataHandler(){}

    void loadTextures(){
        path = pS.getDirPath("data", 3);


        // loading textures from file
        if (!tPlayer.loadFromFile(path.string() + "/Wood.png")){std::cout << "tPlayer did not load";}
        

    }


};