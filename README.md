[![Build Status](https://travis-ci.org/KoroLion/tp_lk_2d_mp_shooter.svg?branch=master)](https://travis-ci.org/KoroLion/tp_lk_2d_mp_shooter)

# Multiplayer 2D Shooter

### Compilation under Windows
0. Clone repository and open its folder
1. Create 2 folders: **src/client/lib** and **src/client/build**
2. Download pre-compiled SDL: [https://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz](SDL2-devel-2.0.12-mingw.tar.gz)
3. Copy **i686-w64-mingw32** from SDL archive to **src/client/lib**
4. Copy **SDL2.dll** from **src/client/lib/i686-w64-mingw32/bin** to **src/client/build**
5. Open PowerShell or CMD in **src/client** and type **make; .\build\client.exe**