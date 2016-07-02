#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <map>

class Keyboard {
    // Stores pressed keys
    std::map<SDL_Keycode, bool> keyDown;

  public:
    void keyPressed(SDL_Keycode);
    void keyReleased(SDL_Keycode);
    bool isDown(SDL_Keycode);
};

#endif // KEYBOARD_H
