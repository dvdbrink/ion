set(INC_DIR ${PROJECT_SOURCE_DIR}/include/ion/gfx/gl)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/source/ion/gfx/gl)

set(SOURCES
    ${SRC_DIR}/clear.cpp
    ${INC_DIR}/draw.hpp
    ${SRC_DIR}/draw.cpp
    ${INC_DIR}/frame_buffer.hpp
    ${SRC_DIR}/frame_buffer.cpp
    ${SRC_DIR}/error.hpp
    ${SRC_DIR}/error.cpp
    ${SRC_DIR}/extensions.h
    ${SRC_DIR}/extensions.c
    ${INC_DIR}/index_buffer.hpp
    ${SRC_DIR}/index_buffer.cpp
    ${SRC_DIR}/map.hpp
    ${INC_DIR}/program.hpp
    ${SRC_DIR}/program.cpp
    ${INC_DIR}/render_buffer.hpp
    ${SRC_DIR}/render_buffer.cpp
    ${INC_DIR}/resource.hpp
    ${INC_DIR}/shader.hpp
    ${SRC_DIR}/shader.cpp
    ${INC_DIR}/texture.hpp
    ${SRC_DIR}/texture.cpp
    ${INC_DIR}/vertex_array.hpp
    ${SRC_DIR}/vertex_array.cpp
    ${INC_DIR}/vertex_buffer.hpp
    ${SRC_DIR}/vertex_buffer.cpp
)

add_library(ion-gfx-gl ${SOURCES})
target_link_libraries(ion-gfx-gl)
