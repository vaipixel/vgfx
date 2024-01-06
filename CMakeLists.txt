cmake_minimum_required(VERSION 3.22.1)
project(vgfx)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES
        src/core/*.*
        src/platform/*.*
        src/*.*)

list(APPEND VGFX_FILES ${SRC_FILES})

add_library(vgfx SHARED ${VGFX_FILES}
)

target_include_directories(vgfx PUBLIC include PRIVATE src)

target_link_libraries(
        vgfx
        log
)