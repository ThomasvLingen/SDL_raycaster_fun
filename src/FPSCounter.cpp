//
// Created by mafn on 9/20/16.
//

#include "FPSCounter.h"

FPSCounter::FPSCounter(SDL_Renderer* renderer) {
    this->renderer = renderer;

    this->render_font = TTF_OpenFont("res/jelmer.ttf", 30);

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
    this->fps = 1000 / (float)timeSinceLastUpdate;
}

std::string FPSCounter::get_fps_text()
{
    std::ostringstream strs;
    strs << "FPS: ";
    strs << (int)this->fps;
    return strs.str();
}


void FPSCounter::draw(SDL_Surface *windowSurface) {
    std::string fps_text = this->get_fps_text();
    SDL_Surface* text_surface = TTF_RenderText_Solid(this->render_font, fps_text.c_str(), this->render_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    SDL_Rect text_rect;
    text_rect.x = 7; // Jelmer is autistic
    text_rect.y = -1;
    text_rect.w = text_surface->w;
    text_rect.h = text_surface->h;

    SDL_RenderCopy(this->renderer, text_texture, nullptr, &text_rect);
}
