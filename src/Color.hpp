//
// Created by mafn on 10/7/2016.
//

#ifndef SDL_RAYCASTER_FUN_COLOR_HPP
#define SDL_RAYCASTER_FUN_COLOR_HPP

#include <SDL2/SDL.h>

class Color {
public:
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Color(Uint8 r, Uint8 g, Uint8 b);
    Color(const Color& other);
    ~Color();

    Color reduce();

    Color& operator=(const Color& other);
};
void set_render_color(SDL_Renderer* renderer, Color& c);


#endif //SDL_RAYCASTER_FUN_COLOR_HPP
