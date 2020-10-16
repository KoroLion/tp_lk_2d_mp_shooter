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
