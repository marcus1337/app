cmake_minimum_required(VERSION 3.23.0)
project(example)
if(EMSCRIPTEN)
    if(NOT DEFINED ENV{CC} OR NOT DEFINED ENV{CXX})
        message(WARNING "Environment variables CC and CXX are not set. Using default paths.")
        set(CMAKE_C_COMPILER /home/zzz/code/tools/emsdk/upstream/emscripten/emcc)
        set(CMAKE_CXX_COMPILER /home/zzz/code/tools/emsdk/upstream/emscripten/em++)
    endif()
endif()

add_executable(${PROJECT_NAME} "main.cpp")

include(FetchContent)
FetchContent_Declare(
  app
  GIT_REPOSITORY https://github.com/marcus1337/app.git
  GIT_TAG dev
)
FetchContent_MakeAvailable(app)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${app_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE app)

