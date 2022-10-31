cmake_minimum_required(VERSION 3.7)
project(game)

# set(SOURCE_FILES
#     cell.c
#     cell.h
#     field.c
#     field.h
#     random.c
#     random.h
# )
file(GLOB SOURCE_FILES "*.c")

add_library(game SHARED STATIC ${SOURCE_FILES})

install(TARGETS game DESTINATION ${MINESWEEPER_INSTALL_LIB_DIR})