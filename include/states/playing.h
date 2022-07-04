#include <gameState.h>

class Playing : public GameState
{
public:
    TextureLoader textureLoader;
    EntityRenderer entityRender;

    Player player;
    std::vector<Renderable*> renderables;

    Playing(){}

    void init(){
        player.init(100,100);
        renderables.push_back(&player);

        textureLoader.loadTextures();

        //test
        renderables.push_back(&player);
    }

    void update(){

    }

    void draw(sf::RenderWindow &pWindow){
        // clear the window with black color
        pWindow.clear(sf::Color::Black);

        // draw all renderables in the vector
        for(int i=0; i<renderables.size(); i++){
        entityRender.render(renderables[i], pWindow, textureLoader);
        }

        // end the current frame
        pWindow.display();
    }
};