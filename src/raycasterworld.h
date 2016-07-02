#ifndef RAYCASTERWORLD_H
#define RAYCASTERWORLD_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

#include "GameObject.h"
#include "player.h"

typedef std::vector<std::vector<int>> World2DVector;

class RaycasterWorld : public GameObject
{
public:
    RaycasterWorld(SDL_Renderer* renderer, Player* player);

    SDL_Renderer* renderer;

    static World2DVector world;
    Player* player;

    virtual void handleInput(Keyboard input)     ;
    virtual void update(int timeSinceLastUpdate) ;
    virtual void draw(SDL_Surface* windowSurface);

    int get_world_tile(int x, int y);
    Uint32 getColor(int id, SDL_Surface* surface);
};

#endif // RAYCASTERWORLD_H
