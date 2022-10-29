cmake_minimum_required(VERSION 3.2)

project(minesweeper_c)

# SDL2
set(SDL2_DIR "C:/dev/lib/SDL2")
set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -pedantic")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(MINESWEEPER_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(MINESWEEPER_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(MINESWEEPER_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${MINESWEEPER_INSTALL_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS}) 

add_subdirectory(src)