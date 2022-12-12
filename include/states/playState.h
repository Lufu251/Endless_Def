#pragma once

#include <gameState.h>

#include <dataHandler.h>
#include <renderableRenderer.h>
#include <worldRenderer.h>
#include <camera.h>
#include <inputHandler.h>
#include <pathFinder.h>
#include <gameController.h>
#include <SFML/Graphics.hpp>

#include <renderable.h>
#include <component.h>
#include <turret.h>
#include <entity.h>
#include <player.h>
#include <enemy.h>
#include <world.h>

#include <chrono>

class PlayState : public GameState
{
private:

public:
    World world;

    std::vector<Renderable*> renderables;
    std::vector<std::unique_ptr<Entity>> entitys;
    std::vector<std::unique_ptr<Component>> components;

    std::vector<sf::Texture> textures;

    InputHandler inputHandler;
    
    GameController gameController;
    PathFinder pF;
    DataHandler dataHandler;
    RenderableRenderer renderableRenderer;
    WorldRenderer worldRenderer;
    Camera gameCamera;

    PlayState(sf::RenderWindow &rWindow): GameState(rWindow){}

    void handleEvents(bool &pRunning){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
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

        inputHandler.newKeyboardKey("key_W", sf::Keyboard::W);
        inputHandler.newKeyboardKey("key_A", sf::Keyboard::A);
        inputHandler.newKeyboardKey("key_S", sf::Keyboard::S);
        inputHandler.newKeyboardKey("key_D", sf::Keyboard::D);
        inputHandler.newMouseButton("left", sf::Mouse::Left);
        
        gameCamera.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
        gameCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

        world.setTileSize(32);
        dataHandler.loadWorldFromFile("world.sv", world);
        addEntity(Player(world.beacorePosition.x() * (float)world.getTileSize(),world.beacorePosition.y() * (float)world.getTileSize(),32,32));
        addEntity(Enemy(400,400,100,100));
        addComponent(Turret(600,600,100,100));
        pF.setGridSize(world.sizeX(), world.sizeY());
        pF.setObstacles(world);
        pF.dijkstra(10,37);
    }

    void update(float &pDeltaTime){
        // check for key input
        inputHandler.update(window);

            gameController.setPlayerDirection(entitys, inputHandler, pDeltaTime);
            entitys[0]->move();
            gameController.worldCollision(world, entitys);
            gameController.worldBorderConstrain(world, entitys);

            gameCamera.follow(entitys[0]->position.x() +entitys[0]->size.x() /2, entitys[0]->position.y() +entitys[0]->size.y() /2);
            gameCamera.constrain(window, world);
            gameCamera.update();

        // reset key states on last call of game update
        inputHandler.updateState();
    }

    void draw(){

        // set the view to 
        window.setView(gameCamera.getView());
            // render all tiles from the world
            worldRenderer.render(world, window, gameCamera, dataHandler);
            // draw all renderables
            sortRenderables();
            renderableRenderer.render(renderables, window, dataHandler);
    }

    void loadTextures(){
        dataHandler.loadTexture("grassT", "grass.png");
        dataHandler.loadTexture("rockT", "rock.png");
        dataHandler.loadTexture("boriumT", "borium.png");
        dataHandler.loadTexture("beacoreT","beacore.png");
        dataHandler.loadTexture("spawnerT","spawner.png");
        dataHandler.loadTexture("playerT","player.png");
        dataHandler.loadTexture("enemyT","enemy.png");
    }

    void addEntity(const auto& rEntity){
        entitys.push_back(std::make_unique<std::remove_cvref_t<decltype(rEntity)>>(rEntity));
        renderables.push_back(entitys.back().get());
    }
    void addComponent(const auto& rComponent){
        components.push_back(std::make_unique<std::remove_cvref_t<decltype(rComponent)>>(rComponent));
        renderables.push_back(components.back().get());
    }
    void sortRenderables(){
        auto compare = [](const Renderable* l, const Renderable* r){
            return l->position.y() + l->size.y() < r->position.y() + r->size.y();
        };
        std::stable_sort(renderables.begin(), renderables.end(), compare);
    }
};