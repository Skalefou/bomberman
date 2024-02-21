cmake_minimum_required(VERSION 3.27)
project(bomberman_SDL2_2 C)

set(CMAKE_C_STANDARD 11)

# Déterminez le chemin vers la SDL2 sur votre système
set(SDL2_INCLUDE_DIR "C:/msys64/mingw64/include/SDL2")
set(SDL2_LIBRARY_DIR "C:/msys64/mingw64/lib")

# Incluez les en-têtes de la bibliothèque SDL2
include_directories(${SDL2_INCLUDE_DIR})

# Ajoutez les fichiers source de votre projet
add_executable(bomberman_SDL2_2
        src/main.c
        src/Game.c
        src/Map.c
        src/Graphics.c
        src/Utils.c
        src/editor.c
        src/editor.h
        src/const.h
        src/Game.h
        src/Graphics.h
        src/Map.h
        src/Utils.h
        src/Player.c
        src/Player.h
        src/Map.c)

# Spécifiez les bibliothèques SDL2 à lier
target_link_directories(bomberman_SDL2_2 PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(bomberman_SDL2_2 PRIVATE mingw32 SDL2main SDL2 SDL2_image)
