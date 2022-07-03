#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>

#include <pathSearcher.h>

class TextureLoader
{
private:
    PathSearcher pS;

public:
    sf::Texture tPlayer;
    const std::filesystem::path path= pS.getDirPath("data", 3);

    TextureLoader(/* args */){}
    ~TextureLoader(){}

    void loadTextures(){

        // loading textures from file
        if (!tPlayer.loadFromFile(path.string() + "/Player.png")){std::cout << "tPlayer did not load";}
        

    }
};