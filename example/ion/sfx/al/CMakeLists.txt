add_executable(ion-sfx-al-example main.cpp)
target_link_libraries(ion-sfx-al-example ion-sfx ion-sfx-al)
add_custom_command(TARGET ion-sfx-al-example POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/example/ion/sfx/al/res $<TARGET_FILE_DIR:ion-sfx-al-example>/res)