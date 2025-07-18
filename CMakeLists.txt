cmake_minimum_required(VERSION 3.14)
project(terminal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración para ejecutable portable
if(WIN32)
    # Linkeo estático para Windows (portable)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
    # Alternativa más compatible si la anterior no funciona:
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

if(UNIX AND NOT APPLE)
    # Linkeo estático para Linux
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Definir el ejecutable
add_executable(terminal
    src/main.cpp
    src/Board.cpp
    src/Cell.cpp
    src/Game.cpp
)

# Incluir directorios de headers
target_include_directories(terminal
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

# Compilación de tests (opcional)
option(BUILD_TESTS "Build test programs" OFF)

if(BUILD_TESTS)
    enable_testing()
    
    add_executable(test_basic
        tests/test_basic.cpp
        src/Board.cpp
        src/Cell.cpp
        src/Game.cpp
    )
    
    target_include_directories(test_basic
        PRIVATE ${PROJECT_SOURCE_DIR}/include
    )
    
    add_test(NAME BasicTests COMMAND test_basic)
endif()

# TODO: Futuro soporte web con Emscripten
# TODO: Futuro soporte para FTXUI (interfaz más avanzada)