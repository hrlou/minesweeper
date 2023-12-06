project(minesweeper)

cmake_minimum_required(VERSION 3.7)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/build/install")

set(MINESWEEPER_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -pedantic")

include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src/game)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} game ${SDL2_LIBRARIES} SDL2_image)

install(TARGETS minesweeper DESTINATION ${MINESWEEPER_INSTALL_DIR})
file(COPY assets DESTINATION ${MINESWEEPER_INSTALL_DIR})
