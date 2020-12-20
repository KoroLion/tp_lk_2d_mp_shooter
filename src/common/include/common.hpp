#ifndef SRC_COMMON_HPP_
#define SRC_COMMON_HPP_

#include <string>
#include <functional>

/** JSON messages standert:
Server->Client:
{"cmd": "objs", "time": .., "arg": [{objid, tid, x, y, rot, hp}, ...]}
{"cmd": "act",  "time": .., "arg": {objid, tid, arg}}

Client->Server
{ "cmd": MOVE_UP, "arg": true/false }
**/

enum NetServerEventType {
    CONNECTED,
    MESSAGE,
    DISCONNECTED
};

namespace ClientCommands {
    enum ClientCommands {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,

        ROTATE,

        SHOOT,
        RELOAD
    };
}

namespace EntityType {
    enum EntityType {
        PLAYER,
        BOX_SMALL,
        BOX_BIG,
        BULLET
    };
}

namespace ActionType {
    enum ActionType {
        NEW_SELF_ID, // own objId
        SHOOT, // who
        DESTROYED // what
    };
}


typedef std::function<void(NetServerEventType, unsigned, std::string)> net_event_callback;
typedef std::function<void(NetServerEventType, std::string)> net_client_event_callback;

#endif
