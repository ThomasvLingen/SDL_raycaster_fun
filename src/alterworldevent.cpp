#include "alterworldevent.h"

AlterWorldEvent::AlterWorldEvent(
        AlterWorldEventConditional conditional,
        int x,
        int y,
        World2DVector new_part)
        : conditional(conditional),
          new_part(new_part)
{
    this->call_x = x;
    this->call_y = y;
}

void AlterWorldEvent::make_call(RaycasterWorld *world)
{
    world->alter_world(
        this->call_x, this->call_y,
        this->new_part.size(), this->new_part[0].size(),
        this->new_part
    );
}
