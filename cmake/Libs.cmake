

if(EMSCRIPTEN)

endif()

if(NOT EMSCRIPTEN)
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

    if(UNIX)
        find_program(CCACHE_PROGRAM ccache)
        find_program(LLD_PROGRAM lld)

        if(CCACHE_PROGRAM)
            set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
            message(STATUS "ccache found: ${CCACHE_PROGRAM}")
        else()
            message(STATUS "ccache not found")
        endif()
        if(LLD_PROGRAM)
            message(STATUS "lld found: ${LLD_PROGRAM}")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
        else()
            message(STATUS "lld not found")
        endif()
    endif()

    if(WIN32)

    endif()
endif()

