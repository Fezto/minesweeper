@echo off
REM Script de demo para mostrar el buscaminas en acción

echo.
echo ========================================
echo  🎯 BUSCAMINAS C++ - DEMO
echo ========================================
echo.
echo Este es un demo del juego de buscaminas
echo desarrollado en C++23 con CMake
echo.
pause

echo.
echo 🏗️ Compilando el proyecto...
mkdir build 2>nul
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

if %ERRORLEVEL% neq 0 (
    echo ❌ Error en la compilación
    exit /b 1
)

echo.
echo ✅ ¡Compilación exitosa!
echo.
echo 🎮 Iniciando el juego...
echo.
echo Instrucciones:
echo - Escribe las dimensiones (ej: 8x6)
echo - Usa formato A5 para revelar o A5 F para bandera
echo - Encuentra todas las minas sin explota
echo.
pause

REM Ejecutar el juego
terminal.exe

echo.
echo 🎉 ¡Demo completado!
echo.
echo 📚 Para ver la documentación completa:
echo    generate-docs.bat
echo.
pause
