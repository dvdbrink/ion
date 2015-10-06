set(INC_DIR ${PROJECT_SOURCE_DIR}/include/ion/sfx)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/source/ion/sfx)

set(SOURCES
    ${INC_DIR}/music.hpp
    ${SRC_DIR}/music.cpp
)

add_library(ion-sfx ${SOURCES})