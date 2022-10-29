cmake_minimum_required(VERSION 3.2)
project(logic C)

set(SOURCE_FILES
    cell.c
    cell.h
    field.c
    field.h
)

add_library(logic SHARED STATIC ${SOURCE_FILES})

install(TARGETS logic DESTINATION ${MINESWEEPER_INSTALL_LIB_DIR})