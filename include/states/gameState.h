#pragma once

#include <inputHandler.h>

class GameState
{
private:
    /* data */
public:

    virtual ~GameState() = default;

    virtual void init() = 0;
    virtual void update(InputHandler &pInputHandler, float &pDeltaTime) = 0;
    virtual void draw() = 0;
    virtual void handleEvents(bool &pRunning) = 0;
};