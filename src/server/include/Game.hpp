#ifndef TP_LK_2D_MP_SHOOTER_GAME_H

#include "Map.hpp"
#include <string>
#include <tuple>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <thread>
#include <mutex>
#include <queue>

class Game{
public:
    Game();
    ~Game();

    void updateObject(unsigned int _id, Command _command, int args = 0);

    //returns all objects, which object with id == _id can see
    std::vector<std::shared_ptr<GameObject>> getObjects(unsigned int _id);

    bool isRunning();

    void start();
    void end();
private:
    void updateMap();

    unsigned int createPlayer(Coordinates coord);
    void createTechnics(Coordinates _coordinates, float _angle);
    void createObstacle(Coordinates _coordinates, float _angle);
    void removePlayer(unsigned int _id);

    //parse json with boost property tree
    void parseConfig();

    struct defaultValues {
        float map_width;
        float map_height;
        std::queue<Coordinates> obstacles_default_coord;
        std::queue<Coordinates> technics_default_coord;
        std::queue<float> obstacles_default_angles;
        std::queue<float> technics_default_angles;
        std::queue<Coordinates> player_default_coord;
        std::queue<float> player_default_angles;

        //hp, width, height, speed, bullets
        std::map<std::string, float> defaults_player;

        //hp, width, height, damage, acceleration, minspeed
        std::map<std::string, float> defaults_bullet;

        //hp, width, height
        std::map<std::string, float> defaults_obstacle;

        //hp, width, height, speed, capacity
        std::map<std::string, float> defaults_technics;
    };

    std::unique_ptr<defaultValues> defaults;
    std::string config_name;
    std::chrono::time_point<std::chrono::steady_clock> time;
    bool running;
    std::shared_ptr<Map> map;

    std::thread updateThread;
    std::mutex mutex;
};
#define TP_LK_2D_MP_SHOOTER_GAME_H

#endif //TP_LK_2D_MP_SHOOTER_GAME_H
