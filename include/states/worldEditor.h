#pragma once

#include <gameState.h>
#include <camera.h>
#include <world.h>
#include <button.h>
#include <dataHandler.h>
#include <Eigen/Core>

class WorldEditor : public GameState
{
public:
    sf::RenderWindow &mWindow;
    buttonHandler bHandler;
    Camera worldCamera;
    Camera uiCamera;
    World world;
    DataHandler dataHandler;
    WorldRenderer worldRenderer;
    Eigen::Vector2f focus;
    int currentType = 0;

    sf::Vector2i positionOld;

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

    void init(InputHandler &pInputHandler){
        dataHandler.setSaveDirectory("data/saves", 3);
        dataHandler.setTextureDirectory("data/textures", 3);
        dataHandler.loadWorldFromFile("world.sv", world);

        loadTextures();

        pInputHandler.newMouseButton("left", sf::Mouse::Left);

        bHandler.setStyle(dataHandler.getTexture("buttonStyleT"), 16);
        bHandler.addButton(button(300,300,200,20), [](){std::cout << "working";});

        world.setTileSize(32);
        focus.x() = float((world.sizeX() * world.getTileSize()) / 2);
        focus.y() = float((world.sizeY() * world.getTileSize()) / 2);
        worldCamera.reset(sf::FloatRect(0.f, 0.f, float(mWindow.getSize().x), float(mWindow.getSize().y)));
        worldCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        uiCamera.reset(sf::FloatRect(0.f, 0.f, float(mWindow.getSize().x), float(mWindow.getSize().y)));
        uiCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    }

    void update(InputHandler &pInputHandler, float &pDeltaTime){
            worldCamera.follow(focus.x(), focus.y());
            worldCamera.update();
            selectTileType(pInputHandler);
            edit();
            moveFocus();
            bHandler.updateButtons(mWindow, pInputHandler);
    }

    void draw(){
        // clear the window with black color
        mWindow.clear(sf::Color::Black);
        // set the view to 
        mWindow.setView(worldCamera.getView());
            // render all tiles from the world
            worldRenderer.render(world, mWindow, worldCamera, dataHandler);

        mWindow.setView(uiCamera.getView());
            displayTileUI();
            bHandler.drawButtons(mWindow);

        // end the current frame
        mWindow.display();
    }

    void loadTextures(){
        dataHandler.loadTexture("grassT", "grass.png");
        dataHandler.loadTexture("rockT", "rock.png");
        dataHandler.loadTexture("boriumT", "borium.png");
        dataHandler.loadTexture("beacoreT","beacore.png");
        dataHandler.loadTexture("spawnerT","spawner.png");
        dataHandler.loadTexture("worldEditorUIT", "worldEditorUI.png");
        dataHandler.loadTexture("worldIconT", "worldIcon.png");
        dataHandler.loadTexture("buttonStyleT", "buttonStyle.png");
    }

    void moveFocus(){
        sf::Vector2i position = sf::Mouse::getPosition();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
             
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
        sprite.setPosition(0, (float)mWindow.getSize().y / 2 -(134 * scale));
        sprite.setColor(sf::Color(255,255,255,255));
        sprite.setScale(scale, scale);
        sprite.setTexture(dataHandler.getTexture("worldEditorUIT"));
        mWindow.draw(sprite);
    }
    
    void selectTileType(InputHandler &pInputHandler){
        /*if(pInputHandler.key_1){
            currentType = 0;
        }
        if(pInputHandler.key_2){
            currentType = 1;
            
        }
        if(pInputHandler.key_3){
            currentType = 2;
            
        }
        if(pInputHandler.key_4){
            currentType = 3;
            
        }
        if(pInputHandler.key_5){
            currentType = 4;
            
        }*/
    }
    void edit(){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);
            sf::Vector2f worldPos = mWindow.mapPixelToCoords(pixelPos, worldCamera.getView());
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