//
// Created by mafn on 10/7/2016.
//

#include "Color.hpp"

Color::Color()
{

}

Color::Color(Uint8 r, Uint8 g, Uint8 b)
    : r(r), g(g), b(b)
{

}

Color::Color(const Color& other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
}

Color::~Color()
{

}

Color Color::reduce()
{
    Uint8 r = this->r / (Uint8)2;
    Uint8 g = this->g / (Uint8)2;
    Uint8 b = this->b / (Uint8)2;

    Color c(r,g,b);

    return c;
}

Color& Color::operator=(const Color &other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;

    return *this;
}

void set_render_color(SDL_Renderer* renderer, Color& c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
}
