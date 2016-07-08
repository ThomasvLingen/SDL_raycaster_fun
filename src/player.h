#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Keyboard.h"
#include "GameObject.h"
#include "vectorutil.h"

class RaycasterWorld;

class Player : public GameObject
{
public:
    Player(SDL_Renderer* renderer);

    SDL_Renderer* renderer;

    RaycasterWorld* world;

    double MOVE_SPEED = 0.005;
    double ROT_SPEED = 0.001;

    double position_x = 2;
    double position_y = 10;
    double dir_x = -1;
    double dir_y = 0;
    double plane_x = 0;
    double plane_y = 0.66;

    double accel = 0;
    double rotation = 0;

    virtual void handleInput(Keyboard input);
    virtual void update(int timeSinceLastUpdate);
    virtual void draw(SDL_Surface* windowSurface);

    bool is_at(int x, int y);

    void mov_stop();
    void mov_forward();
    void mov_backward();
    void rot_stop();
    void rot_right();
    void rot_left();
};

#endif // PLAYER_H
