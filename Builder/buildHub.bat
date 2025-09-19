@echo off
setlocal enabledelayedexpansion

echo === Compilation of PulseHub DLL for Windows ===

rem --- Préparer la liste des fichiers objets ---
set OBJFILES=
for %%f in (ObjectFiles\*.o) do (
    set OBJFILES=!OBJFILES! %%f
)

rem --- Compiler la DLL ---
g++ -shared -Wl,--out-implib,Build/libPulseHub.a -o Build/PulseHub.dll ^
%OBJFILES% ^
src/glad.c ^
src\hubInterface\HubInterface.cpp ^
include/imgui/backends/imgui_impl_glfw.cpp ^
include/imgui/backends/imgui_impl_opengl3.cpp ^
-Iinclude -Iinclude/imgui -Iinclude/imgui/backends -Iinclude/imgui-node -Isrc ^
-LD:/MSYS2/mingw64/lib ^
-lglfw3 -lopengl32 -lm -lassimp -lcomdlg32 -lws2_32 -lwinmm -lmswsock ^
-DBUILDING_DLL -DENGINE_EDITOR -DPULSE_GRAPHIC_OPENGL -DPULSE_WINDOWS -DIMGUI_IMPL_OPENGL_LOADER_GLAD

if errorlevel 1 (
    echo DLL compilation failed.
    exit /b 1
)

echo === Compilation of PulseHub executable for Windows ===

rem --- Compiler l’exécutable ---
g++ -std=c++17 src/main.cpp -o Build/PulseHub.exe ^
-Iinclude -Iinclude/imgui -Iinclude/imgui/backends -Iinclude/imgui-node -Isrc ^
-LBuild -lPulseHub -LD:/MSYS2/mingw64/lib ^
-lglfw3 -lopengl32 -lm -lassimp -lcomdlg32 -lws2_32 -lwinmm -lmswsock ^
-DENGINE_EDITOR -DPULSE_GRAPHIC_OPENGL -DPULSE_WINDOWS -DIMGUI_IMPL_OPENGL_LOADER_GLAD

if errorlevel 1 (
    echo Executable compilation failed.
    exit /b 1
)

echo === Build completed successfully ===
pause
