@echo off
REM Script para generar documentación con Doxygen

echo.
echo ========================================
echo  📚 Generando documentación con Doxygen
echo ========================================
echo.

REM Verificar si Doxygen está instalado
where doxygen >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ❌ Error: Doxygen no está instalado o no está en el PATH
    echo 💡 Instala Doxygen desde: https://www.doxygen.nl/download.html
    pause
    exit /b 1
)

echo 🔧 Ejecutando Doxygen...
doxygen Doxyfile

if %ERRORLEVEL% neq 0 (
    echo ❌ Error al generar la documentación
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ✅ ¡Documentación generada exitosamente!
echo 📁 Los archivos se encuentran en: docs\html\
echo 🌐 Abre docs\html\index.html en tu navegador
echo.

REM Preguntar si desea abrir la documentación
set /p choice="¿Deseas abrir la documentación ahora? (y/n): "

if /i "%choice%" == "y" (
    if exist "docs\html\index.html" (
        echo 🚀 Abriendo documentación...
        start "" "docs\html\index.html"
    ) else (
        echo ❌ No se encontró el archivo index.html
    )
) else (
    echo 👋 Puedes abrir la documentación más tarde desde: docs\html\index.html
)

echo.
pause
