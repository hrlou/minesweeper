cmake_minimum_required(VERSION 3.2)
project(game)

add_subdirectory(logic)

set(SOURCE_FILES main random)

add_executable(game ${SOURCE_FILES})
target_link_libraries(game logic)
target_link_libraries(game ${SDL2_LIBRARIES})

install(TARGETS game DESTINATION ${MINESWEEPER_INSTALL_BIN_DIR})