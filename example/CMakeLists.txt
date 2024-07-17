cmake_minimum_required(VERSION 3.23.0)
project(example)

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

