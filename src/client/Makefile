windows: main.o Game.o Entities.o World.o
	g++ main.o Game.o Entities.o -o ./build/client.exe -L"lib/x86_64-w64-mingw32/lib" -lmingw32 -lSDL2main -lSDL2 -mwindows
#	del *.o

main.o: main.cpp
	g++ -c -o main.o main.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
Game.o: Game.cpp
	g++ -c -o Game.o Game.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
Entities.o: Entities.cpp
	g++ -c -o Entities.o Entities.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
World.o: World.cpp
	g++ -c -o World.o World.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"



macos:
	g++ -c -o main.o main.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game.o game.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game_objects.o game_objects.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ main.o game.o game_objects.o -o ./build/client.out -F/Library/Frameworks -framework SDL2
test:
	python3 -m cpplint *.cpp include/*.hpp
	cppcheck *.cpp include/*.hpp
