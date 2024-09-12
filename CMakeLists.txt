cmake_minimum_required(VERSION 3.29)
project(MomoFSM)

set(CMAKE_CXX_STANDARD 17)

#add_library(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/MomoFSM.cpp)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MomoFSM.cpp
test.cpp)
