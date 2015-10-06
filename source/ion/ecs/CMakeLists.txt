set(INC_DIR ${PROJECT_SOURCE_DIR}/include/ion/ecs)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/source/ion/ecs)

set(SOURCES
    ${INC_DIR}/component.hpp
    ${SRC_DIR}/component.cpp
    ${INC_DIR}/entity.hpp
    ${SRC_DIR}/entity.cpp
    ${INC_DIR}/system.hpp
    ${SRC_DIR}/system.cpp
    ${INC_DIR}/world.hpp
    ${SRC_DIR}/world.cpp
)

add_library(ion-ecs ${SOURCES})