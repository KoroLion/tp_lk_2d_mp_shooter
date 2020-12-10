CC = g++
CFLAGS = -Wall -Werror -Wpedantic

sdl_include = lib/i686-w64-mingw32/include/SDL2
sdl_lib = lib/i686-w64-mingw32/lib

build/game.exe: build/main.o build/game_objects.o build/game.o
	$(CC) $(CFLAGS) -o $@ $^ -L$(sdl_lib) -lmingw32 -lSDL2main -lSDL2 -mwindows
build/main.o: main.cpp | build
	$(CC) $(CFLAGS) -I$(sdl_include) -c -o $@ $<
build/game_objects.o: game_objects.cpp include/game_objects.hpp
	$(CC) $(CFLAGS) -I$(sdl_include) -c -o $@ $<
build/game.o: game.cpp include/game.hpp
	$(CC) $(CFLAGS) -I$(sdl_include) -c -o $@ $<


windows:
	g++ -c -o main.o main.cpp -I"lib/i686-w64-mingw32/include/SDL2"
	g++ -c -o game.o game.cpp -I"lib/i686-w64-mingw32/include/SDL2"
	g++ -c -o game_objects.o game_objects.cpp -I"lib/i686-w64-mingw32/include/SDL2"
	g++ main.o game.o game_objects.o -o ./build/client.exe -L"lib/i686-w64-mingw32/lib" -lmingw32 -lSDL2main -lSDL2 -mwindows
	rm ./*.o
macos:
	g++ -c -o main.o main.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game.o game.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game_objects.o game_objects.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ main.o game.o game_objects.o -o ./build/client.out -F/Library/Frameworks -framework SDL2
test:
	python3 -m cpplint *.cpp include/*.hpp
	cppcheck *.cpp include/*.hpp
