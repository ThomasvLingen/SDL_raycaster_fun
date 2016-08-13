#include "raycasterworld.h"
#include "alterworldevent.h"
#include "sdl2util.h"

World2DVector RaycasterWorld::world = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,0,2,0,1},
    {1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,3,0,2,0,3,0,0,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,4,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
    {1,4,0,0,0,4,4,0,4,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,5,5,5,5,5,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

RaycasterWorld::RaycasterWorld(SDL_Renderer *renderer, Player* player)
{
    this->renderer = renderer;
    this->player = player;

    this->add_alter_world_event(
        new AlterWorldEvent(
            [](RaycasterWorld* world) -> bool {
                return world->player->is_at(9,28);
            },
            6, 27,
            {
                {1, 1, 1}
            }
        )
    );


    this->add_alter_world_event(
        new AlterWorldEvent(
            [](RaycasterWorld* world) -> bool {
                return world->player->is_at(5,28);
            },
            6, 27,
            {
                {1, 0, 1}
            }
        )
    );
}

void RaycasterWorld::handleInput(Keyboard input)
{
}

void RaycasterWorld::update(int timeSinceLastUpdate)
{
    this->update_alter_events();
}

void RaycasterWorld::update_alter_events()
{
    for (AlterWorldEvents::iterator it = this->alter_events.begin(); it != this->alter_events.end(); it++) {
        if ((*it)->conditional(this)) {
            (*it)->make_call(this);
            this->alter_events.erase(it--);
        }
    }
}

void RaycasterWorld::draw(SDL_Surface *windowSurface)
{
    int width = 640;
    int height = 480;

    for (int x = 0; x < width; x++)
    {
        double camera_x = 2 * x / double(width) - 1;
        double ray_position_x = this->player->position_x;
        double ray_position_y = this->player->position_y;
        double ray_dir_x = this->player->dir_x + this->player->plane_x * camera_x;
        double ray_dir_y = this->player->dir_y + this->player->plane_y * camera_x;

        int map_x = int(ray_position_x);
        int map_y = int(ray_position_y);

        double side_dist_x;
        double side_dist_y;

        double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
        double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
        double perp_wall_dist;

        int step_x;
        int step_y;

        int hit = 0;
        int side;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (ray_position_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - ray_position_x) * delta_dist_x;
        }

        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (ray_position_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - ray_position_y) * delta_dist_y;
        }

        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            if (this->world[map_x][map_y] > 0) {
                hit = 1;
            }
        }

        if (side == 0) {
            perp_wall_dist = (map_x - ray_position_x + (1 - step_x) / 2) / ray_dir_x;
        } else {
            perp_wall_dist = (map_y - ray_position_y + (1 - step_y) / 2) / ray_dir_y;
        }

        int line_height = (int)(height / perp_wall_dist);

        int draw_start = -line_height / 2 + height / 2;
        if (draw_start < 0) {
            draw_start = 0;
        }
        int draw_end = line_height / 2 + height / 2;
        if (draw_end >= height) {
            draw_end = height - 1;
        }

        Uint32 color = this->getColor(this->get_world_tile(map_x, map_y), windowSurface);
        if (side == 1) {
            color = SDL2Util::reduce_color(windowSurface, color);
        }
        Uint8 r, g, b;
        SDL_GetRGB(color, windowSurface->format, &r, &g, &b);
        SDL_SetRenderDrawColor(this->renderer, r, g, b, 0xFF);
        SDL_RenderDrawLine(this->renderer, x, draw_start, x, draw_end);
    }
}

int RaycasterWorld::get_world_tile(int x, int y)
{
    return this->world[x][y];
}

void RaycasterWorld::alter_world(int x, int y, int width, int height, World2DVector new_part)
{
    int new_part_x = 0;
    for (int x_to_alter = x; x_to_alter < x + width; x_to_alter++) {
        int new_part_y = 0;
        for (int y_to_alter = y; y_to_alter < y + height; y_to_alter++) {
            if (this->world.size() > x_to_alter && this->world[x_to_alter].size() > y_to_alter) {
                if (new_part[new_part_x][new_part_y] != -1) {
                    this->world[x_to_alter][y_to_alter] = new_part[new_part_x][new_part_y];
                }
            } else {
                printf("Cannot do alter --> doesn't fit in world\n");
            }

            new_part_y++;
        }

        new_part_x++;
    }
}

void RaycasterWorld::add_alter_world_event(AlterWorldEvent *to_add)
{
    this->alter_events.push_back(to_add);
}

Uint32 RaycasterWorld::getColor(int id, SDL_Surface* surface)
{
    SDL_PixelFormat* format = surface->format;

    switch(id) {
        case 1:
            return SDL_MapRGB(format, 0xFF, 0x00, 0x00); break;
        case 2:
            return SDL_MapRGB(format, 0x00, 0xFF, 0x00); break;
        case 3:
            return SDL_MapRGB(format, 0x00, 0x00, 0xFF); break;
        case 4:
            return SDL_MapRGB(format, 0xFF, 0xFF, 0xFF); break;
        default:
            return SDL_MapRGB(format, 0xFF, 0xFF, 0x00); break;
    }
}
