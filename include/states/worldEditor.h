#pragma once


#include <gameState.h>
#include <camera.h>
#include <world.h>
#include <button.h>
#include <dataHandler.h>
#include <Eigen/Core>
#include <string>

class WorldEditor : public GameState
{
public:
    InputHandler inputHandler;
    buttonHandler bHandler;
    Camera worldCamera;
    Camera uiCamera;
    World world;
    DataHandler dataHandler;
    WorldRenderer worldRenderer;
    Eigen::Vector2f focus;
    int currentType = 0;

    sf::Vector2i positionOld;

    WorldEditor(sf::RenderWindow &rWindow, std::string worldName): GameState(rWindow)
    {
        dataHandler.loadWorldFromFile(worldName, world);
    }


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
                dataHandler.saveWorldToFile("editWorld.sv", world);
            }
            if (event.type == sf::Event::Resized){
                // update the view to the new size of the window
                worldCamera.reset(sf::FloatRect(0.f, 0.f, float(event.size.width), float(event.size.height)));
                uiCamera.reset(sf::FloatRect(0.f, 0.f, float(event.size.width), float(event.size.height)));
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                zoomWorld(-event.mouseWheel.delta);
            }
        }
    }

    void init(){
        dataHandler.setSaveDirectory("data/saves", 3);
        dataHandler.setTextureDirectory("data/textures", 3);
        dataHandler.loadFont("arial.ttf");

        dataHandler.loadTexture("grassT", "grass.png");
        dataHandler.loadTexture("rockT", "rock.png");
        dataHandler.loadTexture("boriumT", "borium.png");
        dataHandler.loadTexture("beacoreT","beacore.png");
        dataHandler.loadTexture("spawnerT","spawner.png");
        dataHandler.loadTexture("worldEditorUIT", "worldEditorUI.png");
        dataHandler.loadTexture("worldIconT", "worldIcon.png");
        dataHandler.loadTexture("buttonStyleT", "buttonStyle.png");

        inputHandler.newMouseButton("left", sf::Mouse::Left);
        inputHandler.newMouseButton("right", sf::Mouse::Right);
        inputHandler.newKeyboardKey("key_1", sf::Keyboard::Num1);
        inputHandler.newKeyboardKey("key_2", sf::Keyboard::Num2);
        inputHandler.newKeyboardKey("key_3", sf::Keyboard::Num3);
        inputHandler.newKeyboardKey("key_4", sf::Keyboard::Num4);
        inputHandler.newKeyboardKey("key_5", sf::Keyboard::Num5);

        bHandler.setButtonStyle(dataHandler.getTexture("buttonStyleT"), 16);
        bHandler.setTextStyle(dataHandler.font, sf::Color(0,0,0));

        world.setTileSize(32);
        focus.x() = float((world.sizeX() * world.getTileSize()) / 2);
        focus.y() = float((world.sizeY() * world.getTileSize()) / 2);
        worldCamera.reset(sf::FloatRect(0.f, 0.f, float(window.getSize().x), float(window.getSize().y)));
        worldCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        uiCamera.reset(sf::FloatRect(0.f, 0.f, float(window.getSize().x), float(window.getSize().y)));
        uiCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    }

    void update(float &pDeltaTime){
        // check for key input
        inputHandler.update(window);

            worldCamera.follow(focus.x(), focus.y());
            worldCamera.update();
            selectTileType();
            edit();
            moveFocus(inputHandler);


            bHandler.updateButtons(window, inputHandler);

        // reset key states on last call of game update
        inputHandler.updateState();
    }

    void draw(){
        // set the view to 
        window.setView(worldCamera.getView());
            // render all tiles from the world
            worldRenderer.render(world, window, worldCamera, dataHandler);

        window.setView(uiCamera.getView());
            displayTileUI();
            bHandler.drawButtons(window);
    }

    void moveFocus(InputHandler &inputHandler){
        sf::Vector2i position = sf::Mouse::getPosition();
        if (inputHandler.isMousePressed("right")){
             
            if(position != positionOld){
                focus.x() += positionOld.x - position.x;
                focus.y() += positionOld.y - position.y;
            }
        }
        positionOld = position;
    }
    void zoomWorld(int ticks){
        world.setTileSize(world.getTileSize() -ticks);
        if(world.getTileSize() <= 0){
            world.setTileSize(1);
        }
        else{
            focus.x() += (world.sizeX() * -ticks) / ((world.sizeX() * world.getTileSize()) / focus.x());
            focus.y() += (world.sizeY() * -ticks) / ((world.sizeY() * world.getTileSize()) / focus.y());
        }
    }

    void displayTileUI(){
        sf::Sprite sprite;
        float scale = 2;
        sprite.setPosition(0, (float)window.getSize().y / 2 -(134 * scale));
        sprite.setColor(sf::Color(255,255,255,255));
        sprite.setScale(scale, scale);
        sprite.setTexture(dataHandler.getTexture("worldEditorUIT"));
        window.draw(sprite);
    }
    
    void selectTileType(){
        if(inputHandler.isKeyPressed("key_1")){
            currentType = 0;
        }
        if(inputHandler.isKeyPressed("key_2")){
            currentType = 1;
            
        }
        if(inputHandler.isKeyPressed("key_3")){
            currentType = 2;
            
        }
        if(inputHandler.isKeyPressed("key_4")){
            currentType = 3;
            
        }
        if(inputHandler.isKeyPressed("key_5")){
            currentType = 4;
            
        }
    }
    void edit(){
        if(inputHandler.isMousePressed("left")){
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, worldCamera.getView());
            sf::Vector2i gridPos;
            gridPos.x = int(worldPos.x / float(world.getTileSize()));
            gridPos.y = int(worldPos.y / float(world.getTileSize()));
            gridPos.x = std::clamp(gridPos.x, 0, world.sizeX()-1);
            gridPos.y = std::clamp(gridPos.y, 0, world.sizeY()-1);
            if(currentType != 3){
            world(gridPos.x, gridPos.y).changeType(currentType);
            }
            else{
                world(world.beacorePosition.x(), world.beacorePosition.y()).changeType(0);
                world(gridPos.x, gridPos.y).changeType(currentType);
                world.beacorePosition.x() = gridPos.x;
                world.beacorePosition.y() = gridPos.y;
            }
        }
    }
};