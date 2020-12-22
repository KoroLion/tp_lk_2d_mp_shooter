CC = g++
CFLAGS = -Wall -Werror -Wpedantic -std=c++14
CFLAGS_LITE = -Wall -std=c++14

SERVER_WORLD = ServerWorld.o Game.o Bullet.o GameObject.o Map.o Obstacle.o Player.o Technics.o

build/server.out: build/main.o build/utils.o build/ServerApp.o build/TcpServer.a build/ServerWorld.a | build
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -I"../common" -lboost_system

build/main.o: main.cpp
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<

build/Packet.o: ../common/Packet.cpp ../common/include/Packet.hpp | build
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<
build/TcpServer.a: build/TcpServer.o build/Packet.o
	ar rcs $@ $^

build/ServerWorld.a: build/ServerWorld.o build/Game.o build/Bullet.o build/GameObject.o build/Map.o build/Obstacle.o build/Player.o build/Technics.o
	ar rcs $@ $^
build/%.o: %.cpp include/%.hpp | build
	$(CC) $(CFLAGS_LITE) -I"../common" -I"include" -lboost_system -c -o $@ $<

build/test_net.out: tests/test_net.cpp | build
	$(CC) $(CFLAGS) $< -o $@ -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
test: build/test_net.out | build
	./build/test_net.out

build:
	mkdir build
clear:
	rm build/*.o
