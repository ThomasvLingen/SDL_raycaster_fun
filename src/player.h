#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Keyboard.h"
#include "GameObject.h"
#include "vectorutil.h"

class Player : public GameObject
{
public:
    Player(SDL_Renderer* renderer);

    SDL_Renderer* renderer;

    double MOVE_SPEED = 0.005;
    double ROT_SPEED = 0.005;

    double position_x = 10;
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

    void mov_stop();
    void mov_forward();
    void mov_backward();
    void rot_stop();
    void rot_right();
    void rot_left();
};

#endif // PLAYER_H
