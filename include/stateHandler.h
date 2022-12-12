#pragma once

#include <iostream>
#include <vector>

#include <gameState.h>

class StateHandler
{
    
public:
    // all gameStates
    std::vector<std::unique_ptr<GameState>> states;

    StateHandler(){}

    void changeState(std::unique_ptr<GameState>&& state){
        // delete the last element
        if(!states.empty()){
            states.pop_back();
        }

        // insert new state at the end
        states.push_back(std::move(state));
        states.back()->init();
    }

    void pushBack(std::unique_ptr<GameState>&& state){
        // insert new state at the end
        states.push_back(std::move(state));
        states.back()->init();
    }

    void popState(){
        if(!states.empty()){
            states.pop_back();
        }
    }
};

extern StateHandler stateHandler;