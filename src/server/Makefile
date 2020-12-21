CC = g++
CFLAGS = -Wall -Werror -Wpedantic

build/server.out: build/main.o build/utils.o build/ServerApp.o build/TcpServer.a build/MockWorld.o | build
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -I"../common" -lboost_system

build/main.o: main.cpp
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<
build/%.o: %.cpp include/%.hpp | build
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<

build/Packet.o: ../common/Packet.cpp ../common/include/Packet.hpp | build
	$(CC) $(CFLAGS) -I"../common" -lboost_system -c -o $@ $<
build/TcpServer.a: build/TcpServer.o build/Packet.o
	ar rcs $@ $^

build/test_net.out: tests/test_net.cpp | build
	$(CC) $(CFLAGS) $< -o $@ -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
test: build/test_net.out | build
	./build/test_net.out

build:
	mkdir build
clear:
	rm build/*.o
