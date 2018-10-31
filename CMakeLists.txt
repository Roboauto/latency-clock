cmake_minimum_required(VERSION 3.6.2)
project(latencyclock)
set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)
pkg_check_modules(DEPENDENCIES
        gstreamer-1.0
        gstreamer-video-1.0)

#PLUGIN
set(PLUGIN_SOURCE_FILES
        gsttimeoverlayparse.cpp
        gsttimeoverlayparse.h
        gsttimestampoverlay.cpp
        gsttimestampoverlay.h
        plugin.cpp)

if(${VIBRANTE_PDK})
    list(TRANSFORM DEPENDENCIES_INCLUDE_DIRS PREPEND "${VIBRANTE_PDK}/targetfs")
endif()

add_definitions(${DEPENDENCIES_CFLAGS})
add_library(latencyclock SHARED ${PLUGIN_SOURCE_FILES})

target_link_libraries(latencyclock ${DEPENDENCIES_LDFLAGS})
target_include_directories(latencyclock PUBLIC ${DEPENDENCIES_INCLUDE_DIRS})
target_compile_options(latencyclock PUBLIC ${DEPENDENCIES_CFLAGS_OTHER})

#SERVER
set(SERVER_SOURCE_FILES server.c)

add_executable(server ${SERVER_SOURCE_FILES})
target_link_libraries(server ${DEPENDENCIES_LDFLAGS} -lm)
target_include_directories(server PUBLIC ${DEPENDENCIES_INCLUDE_DIRS})

#CLIENT
set(CLIENT_SOURCE_FILES client.c)

add_executable(client ${CLIENT_SOURCE_FILES})
target_link_libraries(client ${DEPENDENCIES_LDFLAGS})
target_include_directories(client PUBLIC ${DEPENDENCIES_INCLUDE_DIRS})
