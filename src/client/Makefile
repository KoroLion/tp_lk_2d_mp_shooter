CC = g++.exe
CFLAGS_LITE =
CFLAGS =  -Wall -Werror -Wpedantic
sdl_include = lib/i686-w64-mingw32/include/SDL2
sdl_lib = lib/i686-w64-mingw32/lib
boost_root = E:/Installs/boost_1_74_0

run: build/client.exe
	./$<

build/client.exe: build/main.o build/Game.o build/Entities.o build/World.o build/Equipments.o build/Camera.o build/Animations.o build/tcpclient.a
	$(CC) $(CFLAGS) -o $@ $^ -L$(sdl_lib) -lmingw32 -lSDL2main -lSDL2 -mwindows -lws2_32
build/main.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include) -I"../common" -I$(boost_root) -Wno-deprecated-declarations
build/Game.o: Game.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include) -I"../common" -I$(boost_root) -Wno-deprecated-declarations
build/Entities.o: Entities.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include)
build/World.o: World.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include)
build/Equipments.o: Equipments.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include)
build/Camera.o: Camera.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include)
build/Animations.o: Animations.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(sdl_include)

build/Packet.o: ../common/Packet.cpp ../common/include/Packet.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
build/TcpClient.o: TcpClient.cpp include/TcpClient.hpp
	$(CC) $(CFLAGS) -I$(boost_root) -I"../common" -c -o $@ $< -Wno-deprecated-declarations
build/tcpclient.a: build/TcpClient.o build/Packet.o
	ar rcs $@ $^
build/dev.exe: client_example.cpp build/tcpclient.a
	$(CC) $^ -o $@ -I$(boost_root) -I"../common" -lws2_32 -Wno-deprecated-declarations

test:
	python3 -m cpplint *.cpp include/*.hpp
	cppcheck *.cpp include/*.hpp

clear:
	-rm ./build/*.o
	-rm ./build/*.exe
	-rm ./build/*.out
	-rm ./build/*.a
