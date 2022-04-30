cmake_minimum_required(VERSION 3.16)

project (root)

# Config
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/lib)

# Core lib
add_subdirectory(${PROJECT_SOURCE_DIR}/afk)

# Examples
add_subdirectory(${PROJECT_SOURCE_DIR}/examples)