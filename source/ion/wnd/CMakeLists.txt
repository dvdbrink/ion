set(INC_DIR ${PROJECT_SOURCE_DIR}/include/ion/wnd)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/ion/wnd)

set(SOURCES
    ${INC_DIR}/context.hpp
    ${SRC_DIR}/context.cpp
    ${SRC_DIR}/context_impl.hpp
    ${SRC_DIR}/context_impl.cpp
    ${INC_DIR}/event.hpp
    ${INC_DIR}/keyboard.hpp
    ${INC_DIR}/mouse.hpp
    ${INC_DIR}/window.hpp
    ${SRC_DIR}/window.cpp
    ${SRC_DIR}/handle.hpp
    ${SRC_DIR}/window_impl.hpp
    ${SRC_DIR}/window_impl.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    list(APPEND SOURCES ${SRC_DIR}/glx/extensions.h)
    list(APPEND SOURCES ${SRC_DIR}/glx/extensions.c)
    list(APPEND SOURCES ${SRC_DIR}/glx/context_impl.hpp)
    list(APPEND SOURCES ${SRC_DIR}/glx/context_impl.cpp)
    list(APPEND SOURCES ${SRC_DIR}/x11/window_impl.hpp)
    list(APPEND SOURCES ${SRC_DIR}/x11/window_impl.cpp)

    list(APPEND LIBS X11)
    list(APPEND LIBS GL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    list(APPEND SOURCES ${SRC_DIR}/wgl/extensions.h)
    list(APPEND SOURCES ${SRC_DIR}/wgl/extensions.c)
    list(APPEND SOURCES ${SRC_DIR}/wgl/context_impl.hpp)
    list(APPEND SOURCES ${SRC_DIR}/wgl/context_impl.cpp)
    list(APPEND SOURCES ${SRC_DIR}/win32/window_impl.hpp)
    list(APPEND SOURCES ${SRC_DIR}/win32/window_impl.cpp)

    list(APPEND LIBS gdi32)
    list(APPEND LIBS opengl32)
endif()

add_library(ion-wnd ${SOURCES})
target_link_libraries(ion-wnd ${LIBS})
