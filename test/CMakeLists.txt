cmake_minimum_required(VERSION 3.29)
project(MomoFSMTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
add_executable(${PROJECT_NAME} ../src/MomoFSM.cpp test.cpp)
