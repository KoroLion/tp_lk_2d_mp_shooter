#ifndef TP_LK_2D_MP_SHOOTER_EVENT_H
#define TP_LK_2D_MP_SHOOTER_EVENT_H

#include "Command.hpp"

struct Event{
    Event() {
        id = 0;
        command = BUTTON_UP;
        args = 0;
        isEmpty = true;
    }
    Event(unsigned int _id, Command _command, int _args) : id(_id), command(_command), args(_args), isEmpty(false) {}
    unsigned int id;
    Command command;
    int args;
    bool isEmpty;
};
#endif //TP_LK_2D_MP_SHOOTER_EVENT_H
