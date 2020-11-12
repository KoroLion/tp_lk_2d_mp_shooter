#ifndef SRC_INCLUDE_GAMESERVER_HPP_
#define SRC_INCLUDE_GAMESERVER_HPP_

#include <string>
#include <vector>

#include "World.hpp"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif // _WIN32

void sleepcp(int milliseconds);

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif // _WIN32
}

class Socket {
 public:
    int write(std::string data) { return data.length(); }
    std::string read() { return std::string(""); }
};

class Client {
 private:
    int id;
    Socket s;
 public:
    Client(int id, Socket s);
    int get_id() { return id; }
    int send(std::string message) { return s.write(message); };
    std::string recv() { return s.read(); };
};

class UDPServer {
 private:
     std::string bind_adr;
     int port;
 protected:
     std::vector<Client> clients;
     bool serving;
 public:
    UDPServer(std::string bind_adr, int port): bind_adr(bind_adr), port(port),
        serving(false) {}
    ~UDPServer() {}

    Client get_client(int id);
    int send_to_all(std::string message);
    void start() {
        while (serving) {
            for (auto itr = clients.begin(); itr < clients.end(); itr++) {
                std::string data = itr->recv();
            }
        }
    }
    void stop() {
        serving = false;
    }
};

class GameServer: public UDPServer {
 private:
     World *w;
     std::thread notify_clients_thread;
     static std::string stringify_objects(std::vector<GameObject*> objs) {
         return std::string("");
     }
 public:
    GameServer(std::string bind_adr, int port, World *w):
        UDPServer(bind_adr, port), w(w) {}
    ~GameServer() {}

    void notify_clients() {
        while (serving) {
            for (auto itr = clients.begin(); itr < clients.end(); itr++) {
                std::string data = stringify_objects(w->get_objects(itr->get_id()));
                itr->send(data);
            }
            sleepcp(100);
        }
    }


    void start() {
        serving = true;
        notify_clients_thread = std::thread(&GameServer::notify_clients, this);

        while (serving) {
            for (auto itr = clients.begin(); itr < clients.end(); itr++) {
                std::string data = itr->recv();
                Event e;
                w->add_event(itr->get_id(), e);
            }
        }

        notify_clients_thread.join();
    }
};

#endif  // SRC_INCLUDE_GAMESERVER_HPP_
