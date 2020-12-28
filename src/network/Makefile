CC = g++
CFLAGS = -Wall -Werror -Wpedantic -std=c++14

build/%.o: %.cpp include/%.hpp | build
	$(CC) $(CFLAGS) -lboost_system -c -o $@ $<

build/TcpServer.a: build/TcpServer.o build/Packet.o | build
	ar rcs $@ $^
build/TcpClient.a: build/TcpClient.o build/Packet.o | build
	ar rcs $@ $^

build/server_example.out: server_example.cpp build/TcpServer.a | build
	$(CC) $(CFLAGS) $^ -o $@ -lboost_system

check:
	cppcheck *.cpp include/*.hpp
	cpplint *.cpp include/*.hpp

tests/test.out: tests/unit_tests.cpp build/Packet.o
	$(CC) $(CFLAGS) $^ -o $@ -I. -lgtest -lgtest_main -pthread
test: tests/test.out
	./$<

build:
	mkdir build
