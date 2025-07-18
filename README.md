# 🎯 Buscaminas en C++

Un tutorial paso a paso de cómo crear un juego de buscaminas completo en C++23 usando principios de programación moderna.

## ✨ Características

- 🎮 Interfaz de terminal interactiva con colores
- 🔍 Validación robusta de entrada del usuario con regex
- ⚡ Propagación automática de celdas vacías
- 🚩 Sistema de banderas para marcar minas
- 🎯 Detección automática de victoria/derrota
- 🌐 Compatible con Emscripten para compilación web
- 📁 Estructura de proyecto moderna y escalable

## 🚀 Cómo compilar y ejecutar

### Requisitos previos

- **CMake** 3.14 o superior
- **Compilador C++23** (GCC 11+, Clang 13+, MSVC 2022+)

### Compilación nativa

```bash
# Crear directorio de build
mkdir build && cd build

# Configurar con CMake
cmake ..

# Compilar
cmake --build .

# Ejecutar
./terminal          # Linux/macOS
terminal.exe         # Windows
```

### Compilación para web (Emscripten)

```bash
# Instalar Emscripten (una sola vez)
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk && ./emsdk install latest && ./emsdk activate latest
source ./emsdk_env.sh

# Compilar para web
mkdir build-web && cd build-web
emcmake cmake ..
emmake make

# Servir el archivo HTML
python -m http.server 8000
# Abrir http://localhost:8000/terminal.html
```

## 🎮 Cómo jugar

1. **Selecciona las dimensiones** del tablero (ej: `10x8`)
2. **Ingresa coordenadas** en formato `ColumnaFila Acción`:
   - `A5 R` - Revelar celda en columna A, fila 5
   - `B3 F` - Poner/quitar bandera en columna B, fila 3
   - `C7` - Revelar celda (acción por defecto)

### Símbolos del juego

- `#` - Celda oculta
- `F` - Bandera
- `*` - Mina (solo visible al perder)
- `1-8` - Número de minas adyacentes
- ` ` - Celda vacía

## 🏗️ Arquitectura del proyecto

```
terminal/
├── src/                 # Código fuente (.cpp)
│   ├── main.cpp        # Punto de entrada del programa
│   ├── Game.cpp        # Lógica principal del juego
│   ├── Board.cpp       # Gestión del tablero
│   └── Cell.cpp        # Comportamiento de celdas individuales
├── include/            # Archivos de cabecera (.h)
│   ├── Game.h          # Interfaz de la clase Game
│   ├── Board.h         # Interfaz de la clase Board
│   ├── Cell.h          # Interfaz de la clase Cell
│   ├── Message.h       # Utilidades para mensajes
│   ├── Color.h         # Códigos de colores ANSI
│   ├── GameState.h     # Estados del juego (Playing, Won, Lost)
│   ├── CellState.h     # Estados de celda (Hidden, Revealed, Flagged)
│   └── CellContent.h   # Contenido de celda (Empty, Mine, Number)
├── CMakeLists.txt      # Configuración de CMake
└── README.md           # Este archivo
```

## 🔧 Tecnologías y conceptos utilizados

### C++23 Features

- **Structured bindings** para retornos múltiples
- **Range-based for loops** para iteración moderna
- **Smart pointers** y gestión automática de memoria
- **Regular expressions** para validación de entrada

### Principios de diseño

- **Separación de responsabilidades** (Game, Board, Cell)
- **Encapsulación** de datos y comportamientos
- **Composición** sobre herencia
- **RAII** (Resource Acquisition Is Initialization)

### Herramientas

- **CMake** para build system multiplataforma
- **Emscripten** para compilación a WebAssembly
- **Git** para control de versiones

## 🎓 Propósito educativo

Este proyecto está diseñado como tutorial para aprender:

1. **Estructuración de proyectos C++** modernos
2. **Gestión de dependencias** con CMake
3. **Diseño orientado a objetos** aplicado
4. **Manejo de entrada/salida** robusta
5. **Validación de datos** con regex
6. **Algoritmos de juegos** (propagación, detección de victoria)
7. **Compilación multiplataforma** (nativo + web)

## 🐛 Características técnicas destacadas

- **Propagación recursiva** de celdas vacías optimizada
- **Generación aleatoria** de minas con distribución uniforme
- **Validación de coordenadas** robusta con manejo de errores
- **Interfaz de usuario** clara con códigos de color ANSI
- **Densidad de minas** calculada automáticamente (12.5% del tablero)

## 📝 Licencia

Este proyecto es de código abierto y está disponible bajo la licencia MIT.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/nueva-caracteristica`)
3. Commit tus cambios (`git commit -am 'Agregar nueva característica'`)
4. Push a la rama (`git push origin feature/nueva-caracteristica`)
5. Abre un Pull Request

---

⭐ **¿Te gustó el proyecto?** ¡Dale una estrella al repositorio!
