set(RESOURCE_FOLDER "assets")
set(RES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER}")

if(EXISTS "${RES_PATH}")
    if(EMSCRIPTEN)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --embed-file ${RESOURCE_FOLDER}")
    else()
        add_custom_command(
            TARGET ${PROJECT_NAME}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${RES_PATH}"
                "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_FOLDER}"
            COMMENT "Copying '${RESOURCE_FOLDER}' folder to build directory"
        )
    endif()
endif()
