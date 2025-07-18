@echo off
REM Script para crear ejecutable portable de Windows

echo.
echo ========================================
echo  📦 Creando ejecutable portable
echo ========================================
echo.

REM Limpiar build anterior
if exist "build-portable" (
    echo 🧹 Limpiando build anterior...
    rmdir /s /q "build-portable"
)

REM Crear directorio de build
echo 📁 Creando directorio de build...
mkdir build-portable
cd build-portable

REM Configurar con CMake para Release
echo 🔧 Configurando proyecto para Release...
cmake -DCMAKE_BUILD_TYPE=Release ..

if %ERRORLEVEL% neq 0 (
    echo ❌ Error en la configuración
    pause
    exit /b 1
)

REM Compilar
echo 🏗️ Compilando ejecutable portable...
cmake --build . --config Release

if %ERRORLEVEL% neq 0 (
    echo ❌ Error en la compilación
    pause
    exit /b 1
)

REM Verificar que el ejecutable existe
if exist "Release\terminal.exe" (
    echo.
    echo ✅ ¡Ejecutable portable creado exitosamente!
    echo 📍 Ubicación: build-portable\Release\terminal.exe
    echo 📦 Este archivo es completamente portable
    echo.
    
    REM Mostrar tamaño del archivo
    for %%I in ("Release\terminal.exe") do echo 📊 Tamaño: %%~zI bytes
    
    echo.
    echo 🎮 ¿Deseas probar el ejecutable? (y/n)
    set /p choice="> "
    
    if /i "%choice%" == "y" (
        echo.
        echo 🚀 Ejecutando buscaminas...
        "Release\terminal.exe"
    )
    
) else if exist "terminal.exe" (
    echo.
    echo ✅ ¡Ejecutable portable creado exitosamente!
    echo 📍 Ubicación: build-portable\terminal.exe
    echo 📦 Este archivo es completamente portable
    echo.
    
    REM Mostrar tamaño del archivo
    for %%I in ("terminal.exe") do echo 📊 Tamaño: %%~zI bytes
    
    echo.
    echo 🎮 ¿Deseas probar el ejecutable? (y/n)
    set /p choice="> "
    
    if /i "%choice%" == "y" (
        echo.
        echo 🚀 Ejecutando buscaminas...
        "terminal.exe"
    )
) else (
    echo ❌ No se encontró el ejecutable
    echo 🔍 Verificando archivos en el directorio...
    dir /b *.exe
)

echo.
echo 💡 Tip: Puedes distribuir el archivo .exe sin dependencias
echo 🌐 Ideal para subir a GitHub Releases
echo.
pause
