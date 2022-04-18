cmake_minimum_required(VERSION 3.10)

PROJECT(echoServer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-g -Wall")

set(EXECUTABLE_OUTPUT_PATH $PROJECT_SOURCE_DIR/../..)

# add two executable file
add_executable(echoserver echoserver.cpp )
add_executable(echoclient echoclient.cpp)

