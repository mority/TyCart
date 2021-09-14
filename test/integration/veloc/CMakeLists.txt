add_custom_target(
        build_veloc
        ALL
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/install_veloc.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)