#include "Game.hpp"

using namespace std::literals::chrono_literals;

Game::Game(){
    defaults = std::make_unique<defaultValues>();
    this->config_name = "/home/altana/tp_lk_2d_mp_shooter/src/server/config.json";
    this->parseConfig();
    time = std::chrono::steady_clock::now();
    map = std::make_shared<Map>(defaults->map_height, defaults->map_width);
    while (!defaults->obstacles_default_coord.empty()) {
        this->createObstacle(defaults->obstacles_default_coord.front(), defaults->obstacles_default_angles.front());
        defaults->obstacles_default_coord.pop();
        defaults->obstacles_default_angles.pop();
    }
    while (!defaults->technics_default_coord.empty()) {
        this->createObstacle(defaults->technics_default_coord.front(), defaults->technics_default_angles.front());
        defaults->technics_default_coord.pop();
        defaults->technics_default_angles.pop();
    }
}

Game::~Game(){}

MoveDirection Game::getDirection(Command _command, int args) const {
    if (args == 0)
        return NO_MOVE;
    switch (_command){
        case BUTTON_UP: {
            return FORWARD;
        }
        case BUTTON_LEFT: {
            return LEFT;
        }
        case BUTTON_RIGHT: {
            return RIGHT;
        }
        case BUTTON_DOWN: {
            return BACK;
        }
    }
}

void Game::updateObject(unsigned int _id, Command _command, int args){
    const std::lock_guard<std::mutex> lock(mutex);
    switch (_command) {
        case MOUSE_ANGLE: {
            map->turnObject(_id, float(args), this->time);
            break;
        }
        case COMMAND_RELOAD: {
            map->reload(_id, defaults->defaults_player.at("bullets"), this->time);
            break;
        }
        case COMMAND_SHOOT: {
            std::shared_ptr<GameObject> bullet = std::make_shared<Bullet>(
                    0,
                    Coordinates(0, 0),
                    BULLET,
                    this->time,
                    FORWARD,
                    0,
                    defaults->defaults_bullet.at("hp"),
                    defaults->defaults_bullet.at("width"),
                    defaults->defaults_bullet.at("height"),
                    _id,
                    defaults->defaults_bullet.at("speed"),
                    defaults->defaults_bullet.at("damage"),
                    defaults->defaults_bullet.at("acceleration"),
                    defaults->defaults_bullet.at("minSpeed"));
            map->shoot(_id, bullet);
            break;
        }
        default: {
            auto direction = getDirection(_command, args);
            map->setObjectDirection(_id, direction, this->time);
        }
    }
}

//returns all objects, which object with id == _id can see
std::vector<std::shared_ptr<GameObject>> Game::getObjects(unsigned int _id){
    const std::lock_guard<std::mutex> lock(mutex);
    auto objects = map->getObjects(_id);
    return objects;
}

unsigned int Game::createPlayer() {
    if (defaults->player_default_coord.empty())
        return 0;
    std::shared_ptr<GameObject> player = std::make_shared<Player>(
                0,
                defaults->player_default_coord.front(),
                PLAYER,
                this->time,
                NO_MOVE,
                defaults->player_default_angles.front(),
                defaults->defaults_player.at("hp"),
                defaults->defaults_player.at("width"),
                defaults->defaults_player.at("height"),
                defaults->defaults_player.at("speed"),
                (unsigned int)defaults->defaults_player.at("bullets"));
    defaults->player_default_coord.pop();
    defaults->player_default_angles.pop();
    const std::lock_guard<std::mutex> lock(mutex);
    auto player_id = map->addObject(player);
    return player_id;
}

void Game::removePlayer(unsigned int _id) {
    const std::lock_guard<std::mutex> lock(mutex);
    map->removeObject(_id);
}

void Game::createTechnics(Coordinates _coordinates, float _angle) {
    std::shared_ptr<GameObject> technics = std::make_shared<Technics>(
            0,
            _coordinates,
            TECHNICS,
            this->time,
            NO_MOVE,
            _angle,
            defaults->defaults_technics.at("hp"),
            defaults->defaults_technics.at("width"),
            defaults->defaults_technics.at("height"),
            defaults->defaults_technics.at("speed"),
            defaults->defaults_technics.at("capacity"));
    const std::lock_guard<std::mutex> lock(mutex);
    map->addObject(technics);
}

void Game::createObstacle(Coordinates _coordinates, float _angle) {
    std::shared_ptr<GameObject> obstacle = std::make_shared<Obstacle>(
            0,
            _coordinates,
            OBSTACLE,
            this->time,
            NO_MOVE,
            _angle,
            defaults->defaults_obstacle.at("hp"),
            defaults->defaults_obstacle.at("width"),
            defaults->defaults_obstacle.at("height"));
    const std::lock_guard<std::mutex> lock(mutex);
    map->addObject(obstacle);
}


void Game::start() {
    this->running = true;
    this->updateThread = std::thread(&Game::updateMap, this);
}

void Game::end() {
    this->running = false;
    this->updateThread.join();
}

void Game::updateMap() {
    while (this->running) {
        std::this_thread::sleep_for(10ms);
        const std::lock_guard<std::mutex> lock(mutex);
        time = std::chrono::steady_clock::now();
        map->updateObjects(time);
    }
}

void Game::parseConfig() {
    boost::property_tree::ptree root;
    boost::property_tree::read_json(this->config_name, root);

    defaults->map_width = root.get<float>("mapWidth", 10);
    defaults->map_height = root.get<float>("mapHeight", 10);
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("obstacleCoordinates")) {
                    defaults->obstacles_default_coord.push(Coordinates(val.second.get<float>("x"), val.second.get<float>("y")));
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("technicsCoordinates")) {
                    defaults->technics_default_coord.push(Coordinates(val.second.get<float>("x"), val.second.get<float>("y")));
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("playerCoordinates")) {
                    defaults->player_default_coord.push(Coordinates(val.second.get<float>("x"), val.second.get<float>("y")));
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("obstacleAngles")) {
                    defaults->obstacles_default_angles.push(boost::lexical_cast<float>(val.second.data()));
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("technicsAngles")) {
                    defaults->technics_default_angles.push(boost::lexical_cast<float>(val.second.data()));
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("playerAngles")) {
                    defaults->technics_default_angles.push(boost::lexical_cast<float>(val.second.data()));
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("player")) {
                    defaults->defaults_player[val.first] = boost::lexical_cast<float>(val.second.data());
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("bullet")) {
                    defaults->defaults_bullet[val.first] = boost::lexical_cast<float>(val.second.data());
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("obstacle")) {
                    defaults->defaults_obstacle[val.first] = boost::lexical_cast<float>(val.second.data());
                }
    BOOST_FOREACH (boost::property_tree::ptree::value_type &val, root.get_child("technics")) {
                    defaults->defaults_technics[val.first] = boost::lexical_cast<float>(val.second.data());
                }
}

bool Game::isRunning() const{
    return this->running;
}