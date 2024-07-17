
#file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#add_library(${PROJECT_NAME} ${SRC_FILES})
#message("SRC FILES: ${SRC_FILES}")

add_library(${PROJECT_NAME} 
"src/app.cpp" 
"src/error.cpp"
"src/init.cpp")

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${EXTRA_DIRS}
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "include/util/pch.h")
target_link_libraries(${PROJECT_NAME} PRIVATE "${EXTRA_LIBS}")
