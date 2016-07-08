#ifndef ALTERWORLDEVENT_H
#define ALTERWORLDEVENT_H

#include <functional>

#include "raycasterworld.h"

using std::function;

typedef function<bool(RaycasterWorld*)> AlterWorldEventConditional;

class AlterWorldEvent
{
public:
    AlterWorldEvent(AlterWorldEventConditional conditional, int x, int y, World2DVector new_part);
    ~AlterWorldEvent();

    AlterWorldEventConditional conditional;
    int call_x;
    int call_y;
    World2DVector new_part;

    void make_call(RaycasterWorld* world);
};

#endif // ALTERWORLDEVENT_H
