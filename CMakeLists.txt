cmake_minimum_required(VERSION 3.26)
project(bomberman C)

set(CMAKE_C_STANDARD 11)

find_package(SDL REQUIRED)
find_package(SDL_net REQUIRED)
find_package(SDL_ttf REQUIRED)

add_executable(bomberman
        src/main.c
        src/Game.h
        src/Game.c
        src/Graphics.h
        src/Graphics.c
        src/Multiplayer.c
        src/Multiplayer.h
)

target_link_libraries(bomberman PRIVATE ${SDL_LIBRARY} ${SDL_NET_LIBRARY} ${SDL_TTF_LIBRARY})
target_include_directories(bomberman PRIVATE ${SDL_INCLUDE_DIR})