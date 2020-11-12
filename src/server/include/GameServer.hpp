#ifndef SRC_INCLUDE_GAMESERVER_HPP_
#define SRC_INCLUDE_GAMESERVER_HPP_

#include <string>
#include <vector>

class Socket {
    int write(std::string data) { return data.length(); }
    std::string read() { return std::string(""); }
};

class Client {
 private:
    int id;
    Socket s;
 public:
    Client(int id, Socket s);
    int send(std::string message);
};

class UDPServer {
 private:
     std::string bind_adr;
     int port;
     std::vector<Client> clients;
 public:
    UDPServer(std::string bind_adr, int port): bind_adr(bind_adr), port(port) {}
    ~UDPServer() {}

    Client get_client(int id);
    int send_all(std::string message);
    void serve_forever();
};

class GameServer: UDPServer {
 public:
    GameServer(std::string bind_adr, int port): UDPServer(bind_adr, port) {}
    ~GameServer() {}
};

#endif  // SRC_INCLUDE_GAMESERVER_HPP_
