cmake_minimum_required(VERSION 3.26)
project(bomberman C)

set(CMAKE_C_STANDARD 11)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

add_executable(bomberman
        src/main.c
        src/Game.h
        src/Game.c
        src/Graphics.h
        src/Graphics.c
        src/const.h
        src/Utils.c
        src/Utils.h
        src/Map.c
        src/Map.h
        src/Player.c
        src/Player.h
)

target_link_libraries(bomberman PRIVATE ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY})
target_include_directories(bomberman PRIVATE ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE})