#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>

#include <world.h>
#include <pathSearcher.h>

class DataHandler
{
private:
    PathSearcher pS;
    std::filesystem::path texturePath;
    std::filesystem::path savePath;
    std::unordered_map<std::string, sf::Texture> textures;

public:
    
    DataHandler(){}
    ~DataHandler(){}


    void setTextureDirectory(std::string name, int depth){
        texturePath = pS.getDirPath(name, depth);
    }

    void setSaveDirectory(std::string name, int depth){
        savePath = pS.getDirPath(name, depth);
    }
    
    void loadTexture(std::string name, std::string fileName){
        sf::Texture texture;
        if(!texture.loadFromFile(texturePath.string() + "/" + fileName)){
            std::cout << fileName << " could not load \n";
        }
        textures.insert(std::make_pair(name, texture));
    }

    sf::Texture& getTexture(std::string name){
        return textures[name];
    }

    void loadWorldFromFile(std::string fileName, World &pWorld){
        std::ifstream saveFile;
        int xSize = 0;
        int ySize = 0;

        saveFile.open(savePath.string() + "/" + fileName);
        if (saveFile.is_open())
        {
            std::string line;
            std::getline(saveFile, line, 'x');
            xSize = std::stoi(line);

            std::getline(saveFile, line, 'y');
            ySize = std::stoi(line);

            saveFile.ignore();
            std::getline(saveFile, line, 'x');
            pWorld.beacorePosition.x() = std::stoi(line);

            std::getline(saveFile, line, 'y');
            pWorld.beacorePosition.y() = std::stoi(line);

            saveFile.ignore();
            pWorld.resize(xSize, ySize);

            for (int y = 0; y < ySize; y++){
                for (int x = 0; x < xSize; x++){
                    
                    line = saveFile.get();
                    int t = std::stoi(line);
                    pWorld(x,y).changeType(t);

                    // extract the last character if it was the last character of the line
                    if(x == xSize-1){
                        line = saveFile.get();
                    }
                }
            }
            saveFile.close();
        }
        else std::cout << "Unable to open file";
    }

    void saveWorldToFile(std::string fileName, World &pWorld){
        std::ofstream saveFile;

        saveFile.open(savePath.string() + "/" + fileName);
        if (saveFile.is_open())
        {
            saveFile << pWorld.sizeX() << "x" << pWorld.sizeY() << "y" << "\n";
            saveFile << pWorld.beacorePosition.x() << "x" << pWorld.beacorePosition.y() << "y" << "\n";
            for (int y = 0; y < pWorld.sizeY(); y++){
                for (int x = 0; x < pWorld.sizeX(); x++){
                    saveFile << pWorld(x,y).getType();

                    if(x == pWorld.sizeX()-1){
                        saveFile << "\n";
                    }
                }
            }
        }
    }
};