CC := g++
CFLAGS := -Wall -Werror -Wpedantic

build/main.o: main.cpp include/GameServer.hpp include/ServerApp.hpp | build
	$(CC) $(CFLAGS) -c -o $@ $<
build/server.out: build/main.o | build
	$(CC) $(CFLAGS) -o $@ $^
#build/%.o: %.cpp | build
#	$(CC) $(CFLAGS) $< -c -o $@
build/test_net.out: tests/test_net.cpp | build
	$(CC) $(CFLAGS) $< -o $@ -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
test: build/test_net.out | build
	./build/test_net.out
build:
	mkdir build
