CC = g++
CFLAGS = -Wall -Werror -Wpedantic
boost_root = /home/korolion/boost

build/server.out: build/main.o build/TcpServer.o build/Packet.o | build
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -I$(boost_root) -lboost_system

build/TcpServer.o: TcpServer.cpp include/TcpServer.hpp | build
	$(CC) $(CFLAGS) -I$(boost_root) -I"../common" -lboost_system -c -o $@ $<
build/Packet.o: ../common/Packet.cpp ../common/include/Packet.hpp | build
	$(CC) $(CFLAGS) -I$(boost_root) -I"../common" -lboost_system -c -o $@ $<
build/main.o: main.cpp build/Packet.o build/TcpServer.o include/TcpServer.hpp include/ServerApp.hpp include/World.hpp | build
	$(CC) $(CFLAGS) -I"../common" -c -o $@ $<

build/test_net.out: tests/test_net.cpp | build
	$(CC) $(CFLAGS) $< -o $@ -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
test: build/test_net.out | build
	./build/test_net.out
build:
	mkdir build
clean:
	rm build/*.o
