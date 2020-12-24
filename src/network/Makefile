build/%.o: %.cpp include/%.hpp
	$(CC) $(CFLAGS) -lboost_system -c -o $@ $<

build/TcpServer.a: build/TcpServer.o build/Packet.o
	ar rcs $@ $^
build/TcpClient.a: build/TcpClient.o build/Packet.o
	ar rcs $@ $^

check:
	cppcheck *.cpp include/*.hpp
	cpplint *.cpp include/*.hpp
