cmake_minimum_required(VERSION 3.14)
project(terminal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración para ejecutable portable (evitar en Emscripten)
if(NOT EMSCRIPTEN)
    if(WIN32)
        # Linkeo estático para Windows (portable)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc")
        # Alternativa más compatible si la anterior no funciona:
        # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()

    if(UNIX AND NOT APPLE)
        # Linkeo estático para Linux
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()
endif()

# Definir los sources comunes
set(SOURCES_COMMON
        src/Board.cpp
        src/Cell.cpp
        src/Game.cpp
)

# Opciones específicas de Emscripten que deben aplicarse antes de crear el target
if(EMSCRIPTEN)
    # asegura que el ejecutable final tenga sufijo .html independientemente del build type
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # carpeta de salida relativa al build dir
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")
endif()

# Definir el ejecutable (diferente entrypoint para web vs nativo)
if(EMSCRIPTEN)
    # En web usamos un entrypoint sin bloqueo (JS->WASM)
    add_executable(terminal
            ${SOURCES_COMMON}
            src/web_bindings.cpp
    )
else()
    # En nativo usamos el main clásico (stdin bloqueante)
    add_executable(terminal
            src/main.cpp
            ${SOURCES_COMMON}
    )
endif()

# Incluir directorios de headers
target_include_directories(terminal
        PRIVATE ${PROJECT_SOURCE_DIR}/include
)

# Opciones de linkeo/plantilla para Emscripten
if(EMSCRIPTEN)
    add_custom_command(
            TARGET terminal POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${PROJECT_SOURCE_DIR}/web/styles.css
            ${OUTPUT_DIR}/styles.css
            COMMENT "Copiando styles.css a ${OUTPUT_DIR}"
    )

    target_compile_definitions(terminal PRIVATE NO_ANSI_COLORS __EMSCRIPTEN__)
    # Ensure changes to shell/pre.js trigger a relink of terminal.html
    set_property(TARGET terminal APPEND PROPERTY LINK_DEPENDS
            ${PROJECT_SOURCE_DIR}/web/pre.js
            ${PROJECT_SOURCE_DIR}/web/shell.html
            ${PROJECT_SOURCE_DIR}/web/styles.css
    )
    target_link_options(terminal PRIVATE
            "-g"
            "-gsource-map"
            "-sASSERTIONS=2"
            "-sEXPORTED_FUNCTIONS=['_js_init','_js_submit','_js_status_columns','_js_status_rows','_js_status_mines_total','_js_status_flags','_js_status_revealed','_js_status_state']"
            "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
            "-sALLOW_MEMORY_GROWTH=1"
            "-sEXIT_RUNTIME=0"
            "--shell-file" "${PROJECT_SOURCE_DIR}/web/shell.html"
            "--pre-js" "${PROJECT_SOURCE_DIR}/web/pre.js"
    )
endif()

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
