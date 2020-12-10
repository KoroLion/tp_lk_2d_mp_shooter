#ifndef TP_LK_2D_MP_SHOOTER_EVENT_H
#define TP_LK_2D_MP_SHOOTER_EVENT_H

#include "Command.hpp"

struct Event{
    Event(unsigned int _id, Command _command, int _args) : id(_id), command(_command), args(_args) {}
    unsigned int id;
    Command command;
    int args;
};
#endif //TP_LK_2D_MP_SHOOTER_EVENT_H
