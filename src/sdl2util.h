#ifndef SDL2UTIL_H
#define SDL2UTIL_H

#include <SDL2/SDL.h>

class SDL2Util
{
public:
    SDL2Util();
    static Uint32 reduce_color(SDL_Surface* surface, Uint32 color);
};

#endif // SDL2UTIL_H
