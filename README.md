[![Build Status](https://travis-ci.org/KoroLion/tp_lk_2d_mp_shooter.svg?branch=dev)](https://travis-ci.org/KoroLion/tp_lk_2d_mp_shooter)

# LK Multiplayer Shooter

### Compilation under Windows:
0. Clone repository and open its folder
1. Create 2 folders: **src/client/lib** and **src/client/build**
2. Download pre-compiled SDL: [https://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz](SDL2-devel-2.0.12-mingw.tar.gz)
3. Copy **i686-w64-mingw32** from SDL archive to **src/client/lib**
4. Download boost [https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.zip](boost_1_75_0.zip)
5. Copy boost folder to lib. Should be lib/boost/boost/...
6. Copy **SDL2.dll** from **src/client/lib/i686-w64-mingw32/bin** to **src/client/build**
7. Open PowerShell or CMD in **src/client** and type **make build/client.exe; .\build\client.exe**

### Compilation under macOS:
1. Download "Development" [https://www.libsdl.org/download-2.0.php](SDL release) for macOS
2. Open downloaded file and put **SDL2.framework** folder to **/Library/Frameworks**
3. Clone repository and create **src/client/build** folder
4. Navigate to **src/client** with terminal
5. Run **make macos && ./build/client.out**

### Generating docs using doxygen:
1. sudo apt update && sudo apt install doxygen
2. doxygen doxygen_client.dox && doxygen doxygen_server.dox
