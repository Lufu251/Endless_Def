#pragma once

#include <vector>
#include <queue>
#include <world.h>
#include <dachlib.h>

struct Node
{
    sf::Vector2i position;
    sf::Vector2i ancestor;
    float cost = INFINITY;
    Node(){}
    Node(int x, int y):position(x,y), ancestor(x,y){}
    Node(int x, int y, int aX, int aY, float c):position(x,y), ancestor(aX,aY), cost(c){}

    
};

struct CompareCost
{
    bool operator()(Node const& n1, Node const& n2)
    {
        return n1.cost > n2.cost;
    }
};

class PathFinder
{
private:
    bool diagonal = true;
    bool cutCorners = false;
public:
    array_2D<Node> weightedGrid;
    array_2D<int> obstacles;

    PathFinder(){}
    
    void setGridSize(int x, int y){
        // set the size of the grid
        obstacles.resize(x, y);
        // set the size of the cost grid
        weightedGrid.resize(x, y);
    }

    void setObstacles(World &pWorld){

        for (int x = 0; x < pWorld.sizeX(); x++){
            for (int y = 0; y < pWorld.sizeY(); y++){
                if(pWorld(x,y).blocking > 0){
                    obstacles(x,y) = 1;
                }
            }
        }
    }
    
    void dijkstra(int x, int y){
        // lowest QNode is ontop
        std::priority_queue<Node, std::vector<Node>, CompareCost> q;
        // set start node cost to 0
        weightedGrid(x,y).cost = 0;
        // get all neighbors of the start node
        getNeighbors(x, y, q);

        while (!q.empty())
        {   
            // get lowest cost node from queue
            Node n = q.top();
            
            // asigne cost of current nod if queue cost is less
            if(weightedGrid(n.position.x, n.position.y).cost > n.cost){
                // set cost to the cost of the queue Node
                weightedGrid(n.position.x, n.position.y).cost = n.cost;
                // set ancestor to the ancestor of the queue Node
                weightedGrid(n.position.x, n.position.y).ancestor = n.ancestor;
                // set position to the position of the queue Node
                weightedGrid(n.position.x, n.position.y).position = n.position;

                // get list of neighbors and put in queue
                getNeighbors(n.position.x, n.position.y, q);
            }

            // remove lowest cost node from queue
            q.pop();
        }
        
    }

    // return all possible neighbors
    void getNeighbors(int x, int y, std::priority_queue<Node, std::vector<Node>, CompareCost> &rQ){
        float ancestorCost = weightedGrid(x,y).cost;
    // direct Neighbors
        // Top
            // not out of bound
            // not blocking
            // is INFINITY
            if(y-1 >= 0 && obstacles(x,y-1) == 0 && weightedGrid(x,y-1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x, y-1, x, y, ancestorCost + 1));
            }
        // Left
            // not out of bound
            // not blocking
            // is INFINITY
            if(x-1 >= 0 && obstacles(x-1,y) == 0 && weightedGrid(x-1,y).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x-1, y, x, y, ancestorCost + 1));
            }
        // Down
            // not out of bound
            // not blocking
            // is INFINITY
            if(y+1 <= weightedGrid.getSizeY()-1 && obstacles(x,y+1) == 0 && weightedGrid(x,y+1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x, y+1, x, y, ancestorCost + 1));
            }
        // Right
            // not out of bound
            // not blocking
            // is INFINITY
            if(x+1 <= weightedGrid.getSizeY()-1 && obstacles(x+1,y) == 0 && weightedGrid(x+1,y).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x+1, y, x, y, ancestorCost + 1));
            }

    // diagonal Neighbors
        if(diagonal == true){
            float sqrt = std::sqrtf(2.f);
        // Top Left
            // not out of bound
            // not blocking
            // is INFINITY
            if(x-1 >= 0 && y-1 >= 0 && obstacles(x-1,y-1) == 0 && weightedGrid(x-1,y-1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x-1, y-1, x, y, ancestorCost + sqrt));
            }
        // Down Left
            // not out of bound
            // not blocking
            // is INFINITY
            if(x-1 >= 0 && y+1 <= weightedGrid.getSizeY()-1 && obstacles(x-1,y+1) == 0 && weightedGrid(x-1,y+1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x-1, y+1, x, y, ancestorCost + sqrt));
            }
        // Down Right
            // not out of bound
            // not blocking
            // is INFINITY
            if(x+1 <= weightedGrid.getSizeY()-1 && y+1 <= weightedGrid.getSizeY()-1 && obstacles(x+1,y+1) == 0 && weightedGrid(x+1,y+1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x+1, y+1, x, y, ancestorCost + sqrt));
            }
        // Top Right
            // not out of bound
            // not blocking
            // is INFINITY
            if(x+1 <= weightedGrid.getSizeY()-1 && y-1 >= 0 && obstacles(x+1,y-1) == 0 && weightedGrid(x+1,y-1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x+1, y-1, x, y, ancestorCost + sqrt));
            }
        }

    // diagonal Neighbors without cutingcorners
        if(diagonal == true && cutCorners == false){
            float sqrt = std::sqrtf(2.f);
        // Top Left
            // not out of bound
            // not blocking without cutingcorners
            // is INFINITY
            if(x-1 >= 0 && y-1 >= 0 && obstacles(x-1,y-1) == 0  && obstacles(x,y-1) == 0  && obstacles(x-1,y) == 0 && weightedGrid(x-1,y-1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x-1, y-1, x, y, ancestorCost + sqrt));
            }
        // Down Left
            // not out of bound
            // not blocking without cutingcorners
            // is INFINITY
            if(x-1 >= 0 && y+1 <= weightedGrid.getSizeY()-1 && obstacles(x-1,y+1) == 0  && obstacles(x,y+1) == 0 &&  obstacles(x-1,y) == 0 && weightedGrid(x-1,y+1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x-1, y+1, x, y, ancestorCost + sqrt));
            }
        // Down Right
            // not out of bound
            // not blocking without cutingcorners
            // is INFINITY
            if(x+1 <= weightedGrid.getSizeY()-1 && y+1 <= weightedGrid.getSizeY()-1 && obstacles(x+1,y) == 0 && obstacles(x,y+1) == 0 && obstacles(x+1,y+1) == 0 && weightedGrid(x+1,y+1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x+1, y+1, x, y, ancestorCost + sqrt));
            }
        // Top Right
            // not out of bound
            // not blocking without cutingcorners
            // is INFINITY
            if(x+1 <= weightedGrid.getSizeY()-1 && y-1 >= 0 && obstacles(x+1,y-1) == 0 && obstacles(x,y-1) == 0  && obstacles(x+1,y) == 0 && weightedGrid(x+1,y-1).cost == INFINITY){
                // put in queue and asigne atributes
                rQ.push(Node(x+1, y-1, x, y, ancestorCost + sqrt));
            }
        }
    }
};