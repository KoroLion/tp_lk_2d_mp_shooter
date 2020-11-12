CC="C:\CodeBlocks\MinGW\bin\g++.exe"

windows: main.o Game.o Entities.o World.o Equipments.o
	$(CC) -o build/client.exe main.o Game.o Entities.o World.o Equipments.o -L"lib/x86_64-w64-mingw32/lib" -lmingw32 -lSDL2main -lSDL2 -mwindows

main.o: main.cpp
	$(CC) -c -o main.o main.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
Game.o: Game.cpp
	$(CC) -c -o Game.o Game.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
Entities.o: Entities.cpp
	$(CC) -c -o Entities.o Entities.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
World.o: World.cpp
	$(CC) -c -o World.o World.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
Equipments.o: Equipments.cpp
	$(CC) -c -o Equipments.o Equipments.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"


macos:
	g++ -c -o main.o main.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game.o game.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game_objects.o game_objects.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ main.o game.o game_objects.o -o ./build/client.out -F/Library/Frameworks -framework SDL2
test:
	python3 -m cpplint *.cpp include/*.hpp
	cppcheck *.cpp include/*.hpp


clear:
	del *.o *.exe

run: windows
	./build/client.exe