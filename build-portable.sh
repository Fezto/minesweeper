#!/bin/bash

echo
echo "========================================"
echo " 📦 Creando ejecutable portable Linux"
echo "========================================"
echo

# Limpiar build anterior
if [ -d "build-portable" ]; then
    echo "🧹 Limpiando build anterior..."
    rm -rf build-portable
fi

# Crear directorio de build
echo "📁 Creando directorio de build..."
mkdir build-portable
cd build-portable

# Configurar con CMake para Release
echo "🔧 Configurando proyecto para Release..."
cmake -DCMAKE_BUILD_TYPE=Release ..

if [ $? -ne 0 ]; then
    echo "❌ Error en la configuración"
    exit 1
fi

# Compilar
echo "🏗️ Compilando ejecutable portable..."
cmake --build . --config Release

if [ $? -ne 0 ]; then
    echo "❌ Error en la compilación"
    exit 1
fi

# Verificar que el ejecutable existe
if [ -f "terminal" ]; then
    echo
    echo "✅ ¡Ejecutable portable creado exitosamente!"
    echo "📍 Ubicación: build-portable/terminal"
    echo "📦 Este archivo es completamente portable"
    echo
    
    # Mostrar tamaño del archivo
    echo "📊 Tamaño: $(du -h terminal | cut -f1)"
    
    # Hacer ejecutable
    chmod +x terminal
    
    echo
    echo "🎮 ¿Deseas probar el ejecutable? (y/n)"
    read -r choice
    
    if [[ $choice == "y" || $choice == "Y" ]]; then
        echo
        echo "🚀 Ejecutando buscaminas..."
        ./terminal
    fi
    
else
    echo "❌ No se encontró el ejecutable"
    echo "🔍 Verificando archivos en el directorio..."
    ls -la
fi

echo
echo "💡 Tip: Puedes distribuir el archivo sin dependencias"
echo "🌐 Ideal para subir a GitHub Releases"
echo
