#pragma once

#include <gameState.h>
#include <playState.h>

#include <textureEnum.h>
#include <dataHandler.h>
#include <entityRenderer.h>
#include <worldRenderer.h>
#include <camera.h>
#include <inputHandler.h>

#include <renderable.h>
#include <player.h>
#include <enemy.h>
#include <world.h>

class PlayState : public GameState
{
private:

public:
    sf::RenderWindow &mWindow;

    std::vector<Renderable*> renderables;
    std::vector<sf::Texture> textures;
    World world;
    
    DataHandler dataHandler;
    EntityRenderer entityRenderer;
    WorldRenderer worldRenderer;
    Camera gameCamera;

    Player player;

    PlayState(sf::RenderWindow &pWindow): mWindow(pWindow){}

    virtual void handleEvents(bool &pRunning){
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
        dataHandler.setTextureDirectory("data/textures", 3);
        dataHandler.setSaveDirectory("data/saves", 3);
        loadTextures();

        gameCamera.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
        gameCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

        world.setTileSize(32);
        dataHandler.loadWorldFromFile("World2.sv", world);
        dataHandler.saveWorldToFile("World2.sv", world);
        player.init(0,0);

        renderables.push_back(&player);
    }

    void update(InputHandler &pInputHandler){
        
        if(pInputHandler.key_A == true){
            player.move(sf::Vector2f(-3,0));
        }
        if(pInputHandler.key_D == true){
            player.move(sf::Vector2f(3,0));
        }
        if(pInputHandler.key_S == true){
            player.move(sf::Vector2f(0,3));
        }
        if(pInputHandler.key_W == true){
            player.move(sf::Vector2f(0,-3));
        }

        gameCamera.follow(player.position.x, player.position.y);
        gameCamera.constrain(mWindow, world);
        gameCamera.update();
    }

    void draw(){
        // clear the window with black color
        mWindow.clear(sf::Color::Black);

        // set the view to 
        mWindow.setView(gameCamera.getView());
            // render all tiles from the world
            worldRenderer.render(world, mWindow, textures);
            // draw all renderables
            entityRenderer.render(renderables, mWindow, textures);

        // end the current frame
        mWindow.display();
    }

    void loadTextures(){
        textures.push_back(dataHandler.loadTexture("Enemy.png"));
        textures.push_back(dataHandler.loadTexture("Player.png"));
        textures.push_back(dataHandler.loadTexture("Ground.png"));
        textures.push_back(dataHandler.loadTexture("Empty.png"));
    }
};