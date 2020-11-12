#ifndef TP_LK_2D_MP_SHOOTER_EVENT_H
#define TP_LK_2D_MP_SHOOTER_EVENT_H

#include "Command.h"

struct Event{
    unsigned int id;
    Command command;
    int arg;
};
#endif //TP_LK_2D_MP_SHOOTER_EVENT_H
