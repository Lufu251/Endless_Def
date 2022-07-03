#pragma once
#include <renderable.h>
#include <player.h>
#include <vector>

class GameState
{
public:
    Player player;
    std::vector<Renderable*> renderables;
};