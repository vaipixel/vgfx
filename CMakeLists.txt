cmake_minimum_required(VERSION 3.22.1)
project(VGFX)

include(./third_party/vendor_tools/vendor.cmake)

set(CMAKE_CXX_STANDARD 17)

option(VGFX_USE_GAMES_FRAME_PACING "Allow use of Games Frame Pacing as Android sync" OFF)

if (ANDROID)
    set(VGFX_USE_GAMES_FRAME_PACING ON)
endif ()

message("VGFX_USE_GAMES_FRAME_PACING: ${VGFX_USE_GAMES_FRAME_PACING}")

file(GLOB_RECURSE SRC_FILES
        src/core/*.*
        src/platform/default/*.*
        src/gpu/*.*
        src/opengl/*.*
        src/*.*)

if (VGFX_USE_GAMES_FRAME_PACING)
    list(APPEND VGFX_INCLUDES third_party/swappy/include)
endif ()

list(APPEND VGFX_FILES ${SRC_FILES})

if (VGFX_USE_GAMES_FRAME_PACING AND ANDROID)
    list(APPEND VGFX_INCLUDES vendor/swappy/include)
    file(GLOB SWAPPY_LIBS vendor/swappy/${LIBRARY_ENTRY}/*${CMAKE_SHARED_LIBRARY_SUFFIX})
    list(APPEND VGFX_SHARED_LIBS ${SWAPPY_LIBS})
endif ()

if (ANDROID)
    find_library(LOG_LIB log)
    list(APPEND VGFX_SHARED_LIBS ${LOG_LIB})
    find_library(ANDROID_LIB android)
    list(APPEND VGFX_SHARED_LIBS ${ANDROID_LIB})
    find_library(JNIGRAPHICS_LIB jnigraphics)
    list(APPEND VGFX_SHARED_LIBS ${JNIGRAPHICS_LIB})

    file(GLOB_RECURSE PLATFORM_FILES src/platform/android/*.*)
    list(APPEND VGFX_FILES ${PLATFORM_FILES})

    find_library(GLESV2_LIB GLESv2)
    list(APPEND VGFX_SHARED_LIBS ${GLESV2_LIB})
    find_library(EGL_LIB EGL)
    list(APPEND VGFX_SHARED_LIBS ${EGL_LIB})
endif ()

add_vendor_target(vgfx-vendor STATIC_VENDORS ${VGFX_STATIC_VENDORS} SHARED_VENDORS ${VGFX_SHARED_VENDORS})
find_vendor_libraries(vgfx-vendor STATIC VGFX_VENDOR_STATIC_LIBRARIES SHARED TGFX_VENDOR_SHARED_LIBRARIES)
list(APPEND VGFX_STATIC_LIBS ${VGFX_VENDOR_STATIC_LIBRARIES})
list(APPEND VGFX_SHARED_LIBS ${TGFX_VENDOR_SHARED_LIBRARIES})

add_library(vgfx STATIC ${VGFX_FILES})
add_dependencies(vgfx vgfx-vendor)

target_include_directories(vgfx PUBLIC include PRIVATE src)
target_include_directories(vgfx SYSTEM PRIVATE ${VGFX_INCLUDES})

target_link_libraries(
        vgfx
        ${VGFX_SHARED_LIBS}
)