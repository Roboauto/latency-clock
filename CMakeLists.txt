cmake_minimum_required(VERSION 3.6.2)
project(gsttimestampoverlay)
set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)
pkg_check_modules(DEPENDENCIES
        gstreamer-1.0
        gstreamer-video-1.0)

set(SOURCE_FILES
        gsttimeoverlayparse.c
        gsttimeoverlayparse.h
        gsttimestampoverlay.c
        gsttimestampoverlay.h
        plugin.c)

add_definitions(${DEPENDENCIES_CFLAGS})
add_library(gsttimestampoverlay SHARED ${SOURCE_FILES})

target_link_libraries(gsttimestampoverlay ${DEPENDENCIES_LDFLAGS})
target_include_directories(gsttimestampoverlay PUBLIC ${DEPENDENCIES_INCLUDE_DIRS})
target_compile_options(gsttimestampoverlay PUBLIC ${DEPENDENCIES_CFLAGS_OTHER})
