@echo off
setlocal

REM Activar el entorno de Emscripten
call "C:\Users\ayrto\CLionProjects\terminal\emsdk\emsdk_env.bat"

REM Leer parámetro (debug o release)
set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug

REM Determinar carpeta de build
if /I "%BUILD_TYPE%"=="Release" (
    set BUILD_DIR=build-wasm-release
) else (
    set BUILD_DIR=build-wasm
)

echo === Compilando en modo %BUILD_TYPE% en la carpeta %BUILD_DIR% ===

REM Crear build y configurar con Ninja
call emcmake cmake -B %BUILD_DIR% -S . -G Ninja -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

REM Compilar
call cmake --build %BUILD_DIR% -j

REM Solo para Release: copiar archivos a docs/
if /I "%BUILD_TYPE%"=="Release" (
    echo === Preparando carpeta docs/ para GH Pages ===
    if exist "%~dp0docs" rd /s /q "%~dp0docs"
    mkdir "%~dp0docs"

    REM Copiar build
    robocopy "%BUILD_DIR%" "%~dp0docs" /MIR /XF terminal.html /NDL /NFL /NJH /NJS

    REM Copiar archivos web necesarios
    copy "%~dp0web\pre.js" "%~dp0docs\pre.js"
    copy "%~dp0web\shell.html" "%~dp0docs\shell.html"
    copy "%~dp0web\styles.css" "%~dp0docs\styles.css"

    REM Renombrar terminal.html a index.html para GH Pages
    copy "%BUILD_DIR%\terminal.html" "%~dp0docs\index.html"

    REM Crear .nojekyll
    echo.>"%~dp0docs\.nojekyll"

    echo === Docs listo para GH Pages ===
)

REM Servir la app localmente
call emrun %BUILD_DIR%\terminal.html

pause
endlocal
