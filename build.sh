#!/bin/bash

echo
echo "========================================"
echo " 🎯 Buscaminas C++ - Build Script"
echo "========================================"
echo

# Verificar si existe la carpeta build
if [ ! -d "build" ]; then
    echo "📁 Creando directorio build..."
    mkdir build
fi

# Entrar al directorio build
cd build

echo "🔧 Configurando proyecto con CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "❌ Error en la configuración de CMake"
    exit 1
fi

echo "🏗️ Compilando proyecto..."
cmake --build . --config Debug

if [ $? -ne 0 ]; then
    echo "❌ Error en la compilación"
    exit 1
fi

echo
echo "✅ ¡Compilación exitosa!"
echo "🎮 Ejecutable creado: build/terminal"
echo

read -p "¿Deseas ejecutar el juego ahora? (y/n): " choice

if [[ $choice == "y" || $choice == "Y" ]]; then
    echo
    echo "🎯 Iniciando Buscaminas..."
    echo "========================================"
    ./terminal
else
    echo
    echo "👋 ¡Puedes ejecutar el juego más tarde con: ./build/terminal"
fi

echo
