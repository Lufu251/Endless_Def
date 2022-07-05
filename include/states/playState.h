#pragma once
#include <gameState.h>
#include <playState.h>
#include <dataLoader.h>
#include <entityRenderer.h>
#include <renderable.h>
#include <player.h>
#include <textureEnum.h>

class PlayState : public GameState
{
private:
    static PlayState pS;

public:
    DataLoader dataLoader;
    EntityRenderer entityRenderer;

    Player player;
    sf::Texture tPlayer;
    std::vector<Renderable*> renderables;

    std::vector<sf::Texture> textures;

    void init(){
        player.init(100,100);
        renderables.push_back(&player);
        dataLoader.setDirectory("data", 3);

        loadTextures();
    }

    void update(){

    }

    void draw(sf::RenderWindow &pWindow){
        // clear the window with black color
        pWindow.clear(sf::Color::Black);

        // draw all renderables in the vector
        for(int i=0; i<renderables.size(); i++){
        entityRenderer.render(renderables[i], pWindow, textures);
        }

        // end the current frame
        pWindow.display();
    }

    void loadTextures(){
        textures.push_back(dataLoader.loadTexture("Player.png"));
    }
};