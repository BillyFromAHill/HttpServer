cmake_minimum_required (VERSION 2.6)

project (final C CXX)

list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -pthread")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})

include_directories(HttpServer/HttpServer)

include_directories(HttpServer/HttpServer/asio)

add_subdirectory(HttpServer/HttpServer)

SET( CMAKE_EXE_LINKER_FLAGS  "-lpthread" )

