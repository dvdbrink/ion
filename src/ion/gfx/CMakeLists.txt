set(INC_DIR ${PROJECT_SOURCE_DIR}/include/ion/gfx)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/ion/gfx)

set(SOURCES
    ${INC_DIR}/buffer_usage.hpp
    ${INC_DIR}/color.hpp
    ${SRC_DIR}/color.cpp
    ${INC_DIR}/image.hpp
    ${SRC_DIR}/image.cpp
    ${INC_DIR}/material.hpp
    ${INC_DIR}/mesh.hpp
    ${INC_DIR}/pixel_format.hpp
    ${INC_DIR}/primitive_type.hpp
    ${INC_DIR}/scene.hpp
    ${INC_DIR}/type.hpp
)

add_library(ion-gfx ${SOURCES})