set(OPENAL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/al)
find_package(OpenAL REQUIRED)

set(INC_DIR ${PROJECT_SOURCE_DIR}/include/ion/sfx/al)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/source/ion/sfx/al)

set(SOURCES
    ${INC_DIR}/buffer.hpp
    ${SRC_DIR}/buffer.cpp
    ${INC_DIR}/context.hpp
    ${SRC_DIR}/context.cpp
    ${INC_DIR}/device.hpp
    ${SRC_DIR}/device.cpp
    ${SRC_DIR}/error.hpp
    ${SRC_DIR}/error.cpp
    ${INC_DIR}/sound.hpp
    ${SRC_DIR}/sound.cpp
    ${INC_DIR}/source.hpp
    ${SRC_DIR}/source.cpp
)

add_library(ion-sfx-al ${SOURCES})
target_link_libraries(ion-sfx-al ${OPENAL_LIBRARY})