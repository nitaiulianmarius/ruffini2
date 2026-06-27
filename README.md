# Ruffini2

[2015-05]
A two-player fantasy action game written in C++ with SFML, featuring spells, enemies, saves, audio, and animated game states.

## Build and run

Requirements: CMake 3.21+, Git, GNU Make, a MinGW toolchain with `g++` and `mingw32-make`, and vcpkg. The Makefile looks for MinGW in `PATH` first, then in common Windows install locations such as Code::Blocks, MSYS2, and `C:\MinGW`. CMake uses vcpkg to install SFML automatically during the first configuration. The project targets Windows only.

```powershell
make debug
make release
make all
make install
make clean
```

Debug and Release executables are placed in `build/debug/bin` and `build/release/bin`. SFML runtime DLLs and the `data` folder are copied beside each executable automatically. `make install` creates `dist/bin`. Compilation uses the detected number of physical CPU cores.

The minimum source tree is:

```text
CMakeLists.txt
Makefile
vcpkg.json
data/
header/
src/
```

## Features

- Local player-versus-player gameplay
- Fireball, ice, shield, teleport, and invisibility abilities
- Menu, pause, play, and story states
- Sprites, music, sound effects, custom fonts, and save data
