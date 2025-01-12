cmake_minimum_required(VERSION 3.7)
project(game)

set(SOURCE_FILES
    cell.c
    field.c
    random.c
)

add_library(game SHARED STATIC ${SOURCE_FILES})

install(TARGETS game DESTINATION ${MINESWEEPER_INSTALL_LIB_DIR})