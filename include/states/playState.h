#pragma once

#include <gameState.h>
#include <playState.h>

#include <textureEnum.h>
#include <dataHandler.h>
#include <entityRenderer.h>
#include <worldRenderer.h>
#include <camera.h>
#include <inputHandler.h>
#include <pathFinder.h>
#include <gameController.h>

#include <renderable.h>
#include <entity.h>
#include <component.h>
#include <player.h>
#include <enemy.h>
#include <world.h>

#include <chrono>

class PlayState : public GameState
{
private:

public:
    sf::RenderWindow &mWindow;
    World world;

    std::vector<Renderable*> renderables;
    std::vector<std::unique_ptr<Entity>> entitys;
    std::vector<std::unique_ptr<Component>> components;

    std::vector<sf::Texture> textures;
    
    GameController gameController;
    PathFinder pF;
    DataHandler dataHandler;
    EntityRenderer entityRenderer;
    WorldRenderer worldRenderer;
    Camera gameCamera;

    Player player;

    PlayState(sf::RenderWindow &pWindow): mWindow(pWindow){}

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
        dataHandler.setTextureDirectory("data/textures", 3);
        dataHandler.setSaveDirectory("data/saves", 3);
        loadTextures();

        gameCamera.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
        gameCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

        world.setTileSize(48);
        dataHandler.loadWorldFromFile("world.sv", world);
        player.setPosition(200, 200);
        addEntity(Enemy(400,400));
        renderables.push_back(&player);
        pF.setGridSize(world.sizeX(), world.sizeY());
        pF.setObstacles(world);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        //pF.dijkstra(7,7);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }

    void update(InputHandler &pInputHandler, float &pDeltaTime){

        gameController.setPlayerDirection(player, pInputHandler, pDeltaTime);
        player.move();


        gameCamera.follow(player.position.x(), player.position.y());
        gameCamera.constrain(mWindow, world);
        gameCamera.update();
    }

    void draw(){
        // clear the window with black color
        mWindow.clear(sf::Color::Black);

        // set the view to 
        mWindow.setView(gameCamera.getView());
            // render all tiles from the world
            worldRenderer.render(world, mWindow, gameCamera, textures);
            // draw all renderables
            entityRenderer.render(renderables, mWindow, textures);

        // end the current frame
        mWindow.display();
    }

    void loadTextures(){
        textures.push_back(dataHandler.loadTexture("player.png"));
        textures.push_back(dataHandler.loadTexture("Enemy.png"));
        textures.push_back(dataHandler.loadTexture("grass.png"));
        textures.push_back(dataHandler.loadTexture("Empty.png"));
        textures.push_back(dataHandler.loadTexture("rock.png"));
    }

    void addEntity(const auto& rEntity){
        entitys.push_back(std::make_unique<std::remove_cvref_t<decltype(rEntity)>>(rEntity));
        renderables.push_back(entitys.back().get());
    }
};