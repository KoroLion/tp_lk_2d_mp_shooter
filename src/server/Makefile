CC = g++
CFLAGS = -Wall -Werror -Wpedantic
CFLAGS_LITE = -Wall

build/server.out: build/main.o build/TcpServer.o build/Packet.o build/ServerWorld.a | build
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -lboost_system

build/TcpServer.o: TcpServer.cpp include/TcpServer.hpp | build
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<
build/Packet.o: ../common/Packet.cpp ../common/include/Packet.hpp | build
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<
build/main.o: main.cpp build/Packet.o build/TcpServer.o include/TcpServer.hpp include/ServerApp.hpp include/World.hpp | build
	$(CC) $(CFLAGS) -I"../common" -c -o $@ $<

build/ServerWorld.a: build/ServerWorld.o build/Game.o build/Bullet.o build/GameObject.o build/Map.o build/Obstacle.o build/Player.o build/Technics.o
	ar rcs $@ $^
build/%.o: %.cpp include/%.hpp
	$(CC) $(CFLAGS_LITE) -I"../common" -I"include" -c -o $@ $<

build/test_net.out: tests/test_net.cpp | build
	$(CC) $(CFLAGS) $< -o $@ -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
test: build/test_net.out | build
	./build/test_net.out
build:
	mkdir build
clear:
	rm build/*.o
