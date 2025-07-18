@echo off
REM Script de build para Windows

echo.
echo ========================================
echo  🎯 Buscaminas C++ - Build Script
echo ========================================
echo.

REM Verificar si existe la carpeta build
if not exist "build" (
    echo 📁 Creando directorio build...
    mkdir build
)

REM Entrar al directorio build
cd build

echo 🔧 Configurando proyecto con CMake...
cmake ..

if %ERRORLEVEL% neq 0 (
    echo ❌ Error en la configuración de CMake
    pause
    exit /b %ERRORLEVEL%
)

echo 🏗️ Compilando proyecto...
cmake --build . --config Debug

if %ERRORLEVEL% neq 0 (
    echo ❌ Error en la compilación
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ✅ ¡Compilación exitosa!
echo 🎮 Ejecutable creado: build\terminal.exe
echo.
echo ¿Deseas ejecutar el juego ahora? (y/n)
set /p choice="> "

if /i "%choice%" == "y" (
    echo.
    echo 🎯 Iniciando Buscaminas...
    echo ========================================
    terminal.exe
) else (
    echo.
    echo 👋 ¡Puedes ejecutar el juego más tarde con: build\terminal.exe
)

echo.
pause
