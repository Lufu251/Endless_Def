#pragma once

#include <functional>
#include <Eigen/Core>
#include <SFML/Graphics.hpp>
#include <string>

struct button
{
    Eigen::Vector2f position;
    Eigen::Vector2f size;
    std::function<void()> onClick;
    std::string t = "undefined";

    int shade = 255;

    button(){}
    button(int xPosition, int yPosition, int xSize, int ySize, std::string text):position(xPosition, yPosition), size(xSize,ySize), t(text){}
};

struct buttonHandler
{
    int tSize;
    sf::Texture buttonStyle;
    sf::Font font;
    sf::Color textColor = sf::Color(0,0,0);
    std::vector<button> buttons;
    buttonHandler(){

    }

    void updateButtons(sf::RenderWindow &pWindow, InputHandler &pInputHandler){
        for (int i = 0; i < buttons.size(); i++)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(pWindow);
            if(hover(buttons[i], mousePosition)){
                buttons[i].shade = 200;
            }
            else{
                buttons[i].shade = 255;
            }
            if(click(buttons[i], mousePosition, pInputHandler)){
                buttons[i].onClick();
            }
        }
    }

    void drawButtons(sf::RenderWindow &pWindow){
        for (int i = 0; i < buttons.size(); i++)
        {
            float wScale = (buttons[i].size.x() - tSize*2) / tSize;
            float hScale = (buttons[i].size.y() - tSize*2) / tSize;
            
            // center
            sf::Sprite c;
                c.setPosition(buttons[i].position.x()+ tSize, buttons[i].position.y() + tSize);
                c.setTexture(buttonStyle);
                c.setScale(wScale,hScale);
                c.setTextureRect(sf::IntRect(tSize*1,tSize*1,tSize,tSize));
                c.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade, 255));

            // edges
            sf::Sprite t;
                t.setPosition(buttons[i].position.x()+ tSize, buttons[i].position.y());
                t.setTexture(buttonStyle);
                t.setScale(wScale,1);
                t.setTextureRect(sf::IntRect(tSize*1,0,tSize,tSize));
                t.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Sprite d;
                d.setPosition(buttons[i].position.x()+ tSize, buttons[i].position.y() + buttons[i].size.y() - tSize);
                d.setTexture(buttonStyle);
                d.setScale(wScale,1);
                d.setTextureRect(sf::IntRect(tSize*1,tSize*2,tSize,tSize));
                d.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Sprite l;
                l.setPosition(buttons[i].position.x(), buttons[i].position.y() + tSize);
                l.setTexture(buttonStyle);
                l.setScale(1,hScale);
                l.setTextureRect(sf::IntRect(0,tSize*1,tSize,tSize));
                l.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Sprite r;
                r.setPosition(buttons[i].position.x() + buttons[i].size.x() - tSize, buttons[i].position.y() + tSize);
                r.setTexture(buttonStyle);
                r.setScale(1,hScale);
                r.setTextureRect(sf::IntRect(tSize*2,tSize*1,tSize,tSize));
                r.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            // corners
            sf::Sprite tl;
                tl.setPosition(buttons[i].position.x(), buttons[i].position.y());
                tl.setTexture(buttonStyle);
                tl.setScale(1,1);
                tl.setTextureRect(sf::IntRect(0,0,tSize,tSize));
                tl.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Sprite tr;
                tr.setPosition(buttons[i].position.x() + buttons[i].size.x() -tSize, buttons[i].position.y());
                tr.setTexture(buttonStyle);
                tr.setScale(1,1);
                tr.setTextureRect(sf::IntRect(tSize *2,0,tSize, tSize));
                tr.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Sprite dl;
                dl.setPosition(buttons[i].position.x(), buttons[i].position.y() + buttons[i].size.y() -tSize);
                dl.setTexture(buttonStyle);
                dl.setScale(1,1);
                dl.setTextureRect(sf::IntRect(0,tSize *2,tSize,tSize));
                dl.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Sprite dr;
                dr.setPosition(buttons[i].position.x() + buttons[i].size.x() -tSize, buttons[i].position.y() + buttons[i].size.y() -tSize);
                dr.setTexture(buttonStyle);
                dr.setScale(1,1);
                dr.setTextureRect(sf::IntRect(tSize *2,tSize *2,tSize, tSize));
                dr.setColor(sf::Color(buttons[i].shade,buttons[i].shade,buttons[i].shade,255));

            sf::Text text;
                text.setPosition(buttons[i].position.x() + buttons[i].size.x() /2, buttons[i].position.y() + buttons[i].size.y() /2);
                text.setFont(font);
                text.setString(buttons[i].t);
                text.setCharacterSize(12);
                text.setFillColor(textColor);

                sf::Rect BB = text.getLocalBounds();
                text.setOrigin(BB.width /2, BB.height);
                

            pWindow.draw(c);
            pWindow.draw(t);
            pWindow.draw(d);
            pWindow.draw(r);
            pWindow.draw(l);

            pWindow.draw(tl);
            pWindow.draw(tr);
            pWindow.draw(dl);
            pWindow.draw(dr);

            pWindow.draw(text);


        }
    }

    bool hover(button b, sf::Vector2i mP){
        if (mP.x >= b.position.x() &&
            mP.x <= b.position.x() + b.size.x() &&
            mP.y >= b.position.y() &&
            mP.y <= b.position.y() + b.size.y() &&
            !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            ){
                return true;
        }
        return false;
    }

    bool click(button b, sf::Vector2i mP, InputHandler &pInputHandler){
        if (mP.x >= b.position.x() &&
            mP.x <= b.position.x() + b.size.x() &&
            mP.y >= b.position.y() &&
            mP.y <= b.position.y() + b.size.y() &&
            pInputHandler.isMousePressedOnce("left")
            ){
                return true;
        }
        return false;
    }

    void addButton(const button& b, std::function<void()> f){
        buttons.push_back(b);
        buttons.back().onClick = f;
    }

    void setButtonStyle(const sf::Texture &newStyle, int tileSize){
        buttonStyle = newStyle;
        tSize = tileSize;
    }
    void setTextStyle(sf::Font &pFont, sf::Color tColor){
        font = pFont;
        textColor = tColor;
    }
};