#include "player.h"
#include "raycasterworld.h"

Player::Player(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Player::handleInput(Keyboard input)
{
    if (input.isDown(SDLK_w) && input.isDown(SDLK_s)) {
        this->mov_stop();
    } else
    if (input.isDown(SDLK_w)) {
        this->mov_forward();
    } else
    if (input.isDown(SDLK_s)) {
        this->mov_backward();
    } else {
        this->mov_stop();
    }

    if (input.isDown(SDLK_a) && input.isDown(SDLK_d)) {
        this->rot_stop();
    } else
    if (input.isDown(SDLK_a)) {
        this->rot_left();
    } else
    if (input.isDown(SDLK_d)) {
        this->rot_right();
    } else {
        this->rot_stop();
    }
}

void Player::update(int timeSinceLastUpdate)
{
    double moveSpeed = this->accel * timeSinceLastUpdate;
    double new_x = this->position_x + this->dir_x * moveSpeed;
    double new_y = this->position_y + this->dir_y * moveSpeed;
    if (this->world->get_world_tile((int)new_x, (int)new_y) == 0) {
        this->position_x = new_x;
        this->position_y = new_y;
    }

    double rotSpeed = this->rotation * timeSinceLastUpdate;
    VectorUtil::rotate_vector(&this->dir_x, &this->dir_y, rotSpeed);
    VectorUtil::rotate_vector(&this->plane_x, &this->plane_y, rotSpeed);
}

void Player::draw(SDL_Surface *windowSurface)
{
//    SDL_RenderDrawLine(this->renderer, this->position_x, this->position_y, this->position_x + this->dir_x*40, this->position_y + this->dir_y*40);
//    SDL_RenderDrawLine(this->renderer,
//                       this->position_x + this->dir_x*40 - this->plane_x*40, this->position_y + this->dir_y*40 - this->plane_y*40,
//                       this->position_x + this->dir_x*40 + this->plane_x*40, this->position_y + this->dir_y*40 + this->plane_y*40);
}

void Player::mov_stop()
{
    this->accel = 0;
}

void Player::mov_forward()
{
    this->accel = this->MOVE_SPEED;
}

void Player::mov_backward()
{
    this->accel = -this->MOVE_SPEED;
}

void Player::rot_stop()
{
    this->rotation = 0;
}

void Player::rot_right()
{
    this->rotation = -this->ROT_SPEED;
}

void Player::rot_left()
{
    this->rotation = this->ROT_SPEED;
}
