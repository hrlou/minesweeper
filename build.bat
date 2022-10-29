@echo off
DEL bin/*
DEL include/*
MKDIR ./build
CD ./build
cmake ..
cmake --build . --target install --config Release
CD ..