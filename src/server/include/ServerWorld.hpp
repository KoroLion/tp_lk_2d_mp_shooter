#ifndef TP_LK_2D_MP_SHOOTER_SERVERWORLD_H
#define TP_LK_2D_MP_SHOOTER_SERVERWORLD_H

#include "Game.hpp"
#include "Event.hpp"
#include <queue>

class ServerWorld{
public:
    ServerWorld();
    ~ServerWorld();

    void StartGame();
    void EndGame();

    //called by GameServer for each event
    void AddEvent(unsigned int _id, Command _command, int args);

    //called by GameServer and returns all objects, which object with id == _id can see
    std::vector<GameObject *> GetObjects(unsigned int _id);
private:
    void ProcessEvents();

    Game *game;
    std::queue<Event> events;
};
#endif //TP_LK_2D_MP_SHOOTER_SERVERWORLD_H
