#include "sdl2util.h"

SDL2Util::SDL2Util()
{

}

Uint32 SDL2Util::reduce_color(SDL_Surface* surface, Uint32 color)
{
    Uint8 r, g, b;
    SDL_GetRGB(color, surface->format, &r, &g, &b);

    r = r / 2;
    g = g / 2;
    b = b / 2;

    return SDL_MapRGB(surface->format, r, g, b);
}

