CC="C:\CodeBlocks\MinGW\bin\g++.exe"
CFLAGS = -Wall -Werror -Wpedantic
boost_include = E:/Installs/boost_1_74_0/

windows: main.o Game.o Entities.o World.o Equipments.o Camera.o Animations.o  mockUDPClient.o
	$(CC) -o build/client.exe main.o Game.o Entities.o World.o Equipments.o Camera.o Animations.o  mockUDPClient.o \
	-L"lib/x86_64-w64-mingw32/lib" -lmingw32 -lSDL2main -lSDL2 -mwindows \
    -L"lib/gmock-gtest/lib" -lgtest -lgtest_main -lgmock -lgmock_main -pthread

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
Camera.o: Camera.cpp
	$(CC) -c -o Camera.o Camera.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"
mockUDPClient.o: mockUDPClient.cpp
	$(CC) -c -o mockUDPClient.o mockUDPClient.cpp -I"lib/gmock-gtest/include" -I"lib/x86_64-w64-mingw32/include/SDL2"
Animations.o: Animations.cpp
	$(CC) -c -o Animations.o Animations.cpp -I"lib/x86_64-w64-mingw32/include/SDL2"

build/Packet.o: ../common/Packet.cpp ../common/include/Packet.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
build/TcpClient.o: TcpClient.cpp include/TcpClient.hpp
	$(CC) $(CFLAGS) -I$(boost_include) -I"../common" -c -o $@ $< -Wno-deprecated-declarations
build/tcpclient.a: build/TcpClient.o build/Packet.o
	ar rcs $@ $^
build/dev.exe: client_example.cpp build/tcpclient.a
	$(CC) $^ -o $@ -I$(boost_include) -I"../common" -lws2_32 -Wno-deprecated-declarationsmacos:
	g++ -c -o main.o main.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game.o game.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ -c -o game_objects.o game_objects.cpp "-I/Library/Frameworks/SDL2.framework/Headers"
	g++ main.o game.o game_objects.o -o ./build/client.out -F/Library/Frameworks -framework SDL2

test:
	python3 -m cpplint *.cpp include/*.hpp
	cppcheck *.cpp include/*.hpp
clear:
	rm build/*.o
run: windows
	./build/client.exe
