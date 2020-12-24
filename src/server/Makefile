CC = g++
CFLAGS = -Wall -Werror -Wpedantic -std=c++14

build/server.out: build/main.o build/utils.o build/ServerApp.o ../network/build/TcpServer.a build/MockWorld.o | build
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -I"../network" -lboost_system

build/main.o: main.cpp
	$(CC) $(CFLAGS) -I"../network" -I"../common" -lboost_system -c -o $@ $<
build/%.o: %.cpp include/%.hpp | build
	$(CC) $(CFLAGS) -I"../network" -I"../common" -lboost_system -c -o $@ $<

../network/build/TcpServer.a:
	cd ../network && make build/TcpServer.a

build/test_net.out: tests/test_net.cpp | build
	$(CC) $(CFLAGS) $< -o $@ -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
test: build/test_net.out | build
	./build/test_net.out

check:
	cd ../network && make check
	cppcheck *.cpp include/*.hpp
	cpplint *.cpp include/*.hpp
build:
	mkdir build
clear:
	rm build/*.o
