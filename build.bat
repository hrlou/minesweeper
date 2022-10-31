@echo off
rm -r bin
MKDIR bin
CD build
cmake ..
cmake --build . --target clean --config Release
cmake --build . --target install --config Release
CD ..