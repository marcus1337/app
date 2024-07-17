cmake_minimum_required(VERSION 3.23.0)
project(example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")


if(EMSCRIPTEN)
    if(NOT DEFINED ENV{CC} OR NOT DEFINED ENV{CXX})
        message(WARNING "Environment variables CC and CXX are not set. Using default paths.")
        set(CMAKE_C_COMPILER /home/zzz/code/tools/emsdk/upstream/emscripten/emcc)
        set(CMAKE_CXX_COMPILER /home/zzz/code/tools/emsdk/upstream/emscripten/em++)
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s INITIAL_MEMORY=128MB")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_WEBGL2=1 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=['png'] -s USE_SDL_MIXER=2" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s FULL_ES2=1 -s EXPORT_BINDINGS=1 -s ALLOW_MEMORY_GROWTH=1 -std=c++20 --bind -sEXIT_RUNTIME" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s EXPORT_BINDINGS=1 -s ALLOW_MEMORY_GROWTH=1 -std=c++20 --bind")
else()

find_package(SDL2 REQUIRED)
list(APPEND EXTRA_LIBS SDL2::SDL2)
find_package(SDL2_image REQUIRED)
list(APPEND EXTRA_LIBS SDL2_image::SDL2_image)
find_package(SDL2_ttf REQUIRED)
list(APPEND EXTRA_LIBS SDL2_ttf::SDL2_ttf)
find_package(SDL2_mixer REQUIRED)
list(APPEND EXTRA_LIBS SDL2_mixer::SDL2_mixer)
set(MIMALLOC_BUILD_SHARED OFF CACHE BOOL "" FORCE)
find_package(mimalloc REQUIRED)
list(APPEND EXTRA_LIBS mimalloc)

endif()

add_executable(${PROJECT_NAME} "main.cpp")

if(EMSCRIPTEN)
  include(FetchContent)
  FetchContent_Declare(
    app
    GIT_REPOSITORY https://github.com/marcus1337/app.git
    GIT_TAG dev
  )
  FetchContent_MakeAvailable(app)
  list(APPEND EXTRA_LIBS app)
else()
  add_subdirectory(${CMAKE_SOURCE_DIR}/.. ${CMAKE_BINARY_DIR}/app_build)
  list(APPEND EXTRA_LIBS app)
endif()



target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${app_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE "${EXTRA_LIBS}")



