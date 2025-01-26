cmake_minimum_required(VERSION 3.13)
project(WiiControllrtTest VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2 SDL2_ttf SDL2_image SDL2_mixer)

# Configurar rutas ABSOLUTAS
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${DEVKITPRO}/portlibs/wii/include/SDL2 ${DEVKITPRO}/portlibs/wii/include/ ${DEVKITPRO}/devkitPPC/powerpc-eabi/include/)

# Importar biblioteca estática con verificación explícita
add_library(raylib STATIC IMPORTED)

# Verifica que el archivo exista ANTES de configurar la ubicación
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib.a")
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib.a"
    )
else()
    message(FATAL_ERROR "raylib.a no encontrado en: ${CMAKE_CURRENT_SOURCE_DIR}/lib/")
endif()

set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib.a"
)

set(PROG "WiiControllerTest")

function(add_resource out_var)
    set(result)
    foreach(in_f ${ARGN})
        string(MAKE_C_IDENTIFIER ${in_f} input_identifier)
        set(out_f "${CMAKE_CURRENT_BINARY_DIR}/${input_identifier}.o")

        add_custom_command(
            OUTPUT ${out_f}
            COMMAND ${CMAKE_LINKER} --relocatable --format binary --output ${out_f} ${in_f}
            DEPENDS ${in_f}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Embedding ${in_f} as a resource"
        )
        list(APPEND result ${out_f})
    endforeach()
    set(${out_var} ${result} PARENT_SCOPE)
endfunction()

# Archivos de recursos
add_resource(IMAGES "images.data")
add_resource(FONTS "mario286.ttf")

add_executable(${PROG} main.cpp ${IMAGES} ${FONTS})
target_link_libraries(${PROG} PUBLIC
    PkgConfig::SDL2
    raylib
)

if(NINTENDO_WII)
    target_compile_definitions(${PROG} PRIVATE
        NINTENDO_WII
    )

    ogc_create_dol(${PROG})
endif()

set(CMAKE_C_FLAGS_DEBUG "-g -Og -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -Wall -Wextra")
