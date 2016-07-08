#ifndef RAYCASTERWORLD_H
#define RAYCASTERWORLD_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

#include "GameObject.h"
#include "player.h"

class AlterWorldEvent;

typedef std::vector<std::vector<int>> World2DVector;
typedef std::vector<AlterWorldEvent*> AlterWorldEvents;

class RaycasterWorld : public GameObject
{
public:
    RaycasterWorld(SDL_Renderer* renderer, Player* player);

    SDL_Renderer* renderer;

    static World2DVector world;
    Player* player;

    AlterWorldEvents alter_events;
    void update_alter_events();
    void add_alter_world_event(AlterWorldEvent* to_add);

    virtual void handleInput(Keyboard input)     ;
    virtual void update(int timeSinceLastUpdate) ;
    virtual void draw(SDL_Surface* windowSurface);

    void alter_world(int x, int y, int width, int height, World2DVector new_part);
    int get_world_tile(int x, int y);
    Uint32 getColor(int id, SDL_Surface* surface);
};

#endif // RAYCASTERWORLD_H
