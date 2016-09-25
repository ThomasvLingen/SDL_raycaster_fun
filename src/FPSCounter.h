//
// Created by mafn on 9/20/16.
//

#ifndef SDL_RAYCASTER_FUN_FPSCOUNTER_H
#define SDL_RAYCASTER_FUN_FPSCOUNTER_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "GameObject.h"
#include "Keyboard.h"

class FPSCounter : public GameObject{
public:
    bool is_active = true;
    double fps = -1;

    SDL_Renderer* renderer;
    TTF_Font* render_font;
    SDL_Color render_color = { 255, 255, 255, 255 }; // white

    FPSCounter(SDL_Renderer* renderer);

    virtual void handleInput(Keyboard input);
    virtual void update(int timeSinceLastUpdate);
    virtual void draw(SDL_Surface* windowSurface);
};


#endif //SDL_RAYCASTER_FUN_FPSCOUNTER_H
