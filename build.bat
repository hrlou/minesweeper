@echo off
rm -r bin
MKDIR bin
CD build
cmake ..
cmake --build . --target clean --config Release
cmake --build . --target install --config Release
CD ..
for %%x in ("SDL2.dll" "SDL2_image.dll" "jpeg62.dll" "libpng16.dll" "tiff.dll" "webp.dll" "zlib1.dll") do (
    COPY C:\dev\vcpkg\installed\x64-windows\bin\%%x bin\ 
)

COPY C:\dev\vcpkg\packages\liblzma_x64-windows\bin\liblzma.dll bin\

@REM 