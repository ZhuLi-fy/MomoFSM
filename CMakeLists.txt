cmake_minimum_required(VERSION 3.29)
project(MomoFSM VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} src/MomoFSM.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>)
set_target_properties(MomoFSM PROPERTIES PUBLIC_HEADER "include/MomoFSM.h")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(CONFIG_FILE_PATH lib/cmake/${PROJECT_NAME})

write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${CONFIG_FILE_PATH}
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
)
install(
        EXPORT ${PROJECT_NAME}Targets
        DESTINATION ${CONFIG_FILE_PATH}
)

install(FILES
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CONFIG_FILE_PATH}
)
