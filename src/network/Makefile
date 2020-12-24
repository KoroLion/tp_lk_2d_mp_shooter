CC = g++
CFLAGS = -Wall -Werror -Wpedantic -std=c++14

build/%.o: %.cpp include/%.hpp | build
	$(CC) $(CFLAGS) -lboost_system -c -o $@ $<

build/TcpServer.a: build/TcpServer.o build/Packet.o | build
	ar rcs $@ $^
build/TcpClient.a: build/TcpClient.o build/Packet.o | build
	ar rcs $@ $^

check:
	cppcheck *.cpp include/*.hpp
	cpplint *.cpp include/*.hpp

build:
	mkdir build
