#pragma once

#include <gameState.h>
#include <camera.h>
#include <world.h>
#include <dataHandler.h>
#include <Eigen/Core>

class WorldEditor : public GameState
{
public:
    sf::RenderWindow &mWindow;
    Camera gameCamera;
    World world;
    DataHandler dataHandler;
    WorldRenderer worldRenderer;
    Eigen::Vector2f focus;

    std::vector<sf::Texture> textures;

    WorldEditor(sf::RenderWindow &pWindow): mWindow(pWindow){}


    void handleEvents(bool &pRunning){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                mWindow.close();
                pRunning = false;
                std::cout << "window closed";
            }
            if (event.type == sf::Event::Resized){
                // update the view to the new size of the window
                gameCamera.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
            }
        }
    }

    void init(){
        dataHandler.setSaveDirectory("data/saves", 3);
        dataHandler.setTextureDirectory("data/textures", 3);
        dataHandler.loadWorldFromFile("world.sv", world);

        world.setTileSize(32);
        loadTextures();
        focus.x() = 5000;
        focus.y() = 5000;
        gameCamera.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
        gameCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    }

    void update(InputHandler &pInputHandler, float &pDeltaTime){
        gameCamera.follow(focus.x(), focus.y());
        //gameCamera.constrain(mWindow, world);
        gameCamera.update();

    }

    void draw(){
        // clear the window with black color
        mWindow.clear(sf::Color::Black);

        // set the view to 
        mWindow.setView(gameCamera.getView());
            // render all tiles from the world
            worldRenderer.render(world, mWindow, gameCamera, textures);

        // end the current frame
        mWindow.display();
    }

    void loadTextures(){
        textures.push_back(dataHandler.loadTexture("grass.png"));
        textures.push_back(dataHandler.loadTexture("rock.png"));
        textures.push_back(dataHandler.loadTexture("borium.png"));
        textures.push_back(dataHandler.loadTexture("beacore.png"));
        textures.push_back(dataHandler.loadTexture("spawner.png"));
    }
};