target:
	g++ -c -o main.o main.cpp -I"lib/i686-w64-mingw32/include/SDL2"
	g++ -c -o game.o game.cpp -I"lib/i686-w64-mingw32/include/SDL2"
	g++ main.o game.o -o ./build/client.exe -L"lib/i686-w64-mingw32/lib" -lmingw32 -lSDL2main -lSDL2 -mwindows
	rm ./*.o