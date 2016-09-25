//
// Created by mafn on 9/20/16.
//

#include "FPSCounter.h"

FPSCounter::FPSCounter(SDL_Renderer* renderer) {
    this->renderer = renderer;

    this->render_font = TTF_OpenFont("terminus.ttf", 12);

    if (this->render_font == nullptr) {
        printf("Could not open terminus.ttf [%s]\n", TTF_GetError());
    }
}

void FPSCounter::handleInput(Keyboard input) {
    if (input.isDown(SDLK_TAB)) {
        this->is_active = !this->is_active;
    }
}

void FPSCounter::update(int timeSinceLastUpdate) {
    // this->fps = 1000 / timeSinceLastUpdate;
}

void FPSCounter::draw(SDL_Surface *windowSurface) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(this->render_font, "Hallo", this->render_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    SDL_Rect text_rect;
    text_rect.x = 100;
    text_rect.y = 100;

    SDL_RenderCopy(this->renderer, text_texture, nullptr, &text_rect);
}