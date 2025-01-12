# On Windows:
# mkdir build; cd build
# cmake -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake ..
# cmake --build . --config Release

project(minesweeper)

cmake_minimum_required(VERSION 3.7)

# set(SDL2_DIR C:/src/vcpkg/installed/x64-windows/share/sdl2)
# set(SDL2-image_DIR C:/src/vcpkg/installed/x64-windows/share/sdl2-image)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

set(BUILD_DIR "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_INSTALL_PREFIX "${BUILD_DIR}/Release")

set(MINESWEEPER_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -pedantic")

include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src/game)

# file(GLOB SOURCE_FILES "src/*.c")
set(SOURCE_FILES 
    "src/main.c"
    "src/event.c"
    "src/session.c"
    "src/sprite.c"
)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SOURCE_FILES
        ${SOURCE_FILES} 
        "src/debug.c"
    )
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} 
    game
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)

install(TARGETS minesweeper DESTINATION ${MINESWEEPER_INSTALL_DIR})
file(COPY assets DESTINATION ${MINESWEEPER_INSTALL_DIR})
