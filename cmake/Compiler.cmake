
if(EMSCRIPTEN)
    set(CMAKE_C_COMPILER emcc)
    set(CMAKE_CXX_COMPILER em++)
elseif(UNIX)
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
