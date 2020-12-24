#ifndef TP_LK_2D_MP_SHOOTER_SERVERWORLD_H
#define TP_LK_2D_MP_SHOOTER_SERVERWORLD_H

#include "Game.hpp"
#include "Event.hpp"
#include <queue>

class ServerWorld{
public:
    ServerWorld();
    ~ServerWorld();

    void startGame();
    void endGame();

    bool isRunning() const;

    //called by GameServer for each event
    void addEvent(unsigned int _id, Command _command, int args);

    //called by GameServer and returns all objects, which object with id == _id can see
    std::vector<std::shared_ptr<GameObject>> getObjects(unsigned int _id);

    unsigned int connectPlayer();
    void disconnectPlayer(unsigned int _id);
private:
    void handleEvents();

    std::shared_ptr<Game> game;
    std::queue<Event> events;

    std::thread eventsThread;
    std::mutex mutex;
};
#endif //TP_LK_2D_MP_SHOOTER_SERVERWORLD_H
