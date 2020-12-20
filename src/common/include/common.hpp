#ifndef SRC_COMMON_HPP_
#define SRC_COMMON_HPP_

/** JSON messages standert:
Server->Client:
{"cmd": "objs", "time": .., "arg": [{objid, tid, x, y, rot, hp}, ...]}
{"cmd": "act",  "time": .., "arg": {objid, tid, arg}}

Client->Server
{ "cmd": MOVE_UP, "arg": true/false }
**/

namespace NetEventType {
    enum NetEventType {
        CONNECTED,
        RECEIVED,
        DISCONNECTED
    };
}

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
        PLAYER_CONNECTED, // objId = Player's objId
        SELF_CONNECTED, // objId = own
        SHOOT, // who
        DESTROYED // what/who
    };
}

#endif
