cmake_minimum_required(VERSION 3.14)

project (root VERSION 1.0.0 LANGUAGES CXX)

# Config
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/lib)

# Submodule libs
add_subdirectory(${EXTERNAL_DIR}/entt EXCLUDE_FROM_ALL)

# Core lib
add_subdirectory(${PROJECT_SOURCE_DIR}/afk)

# Examples
add_subdirectory(${PROJECT_SOURCE_DIR}/examples EXCLUDE_FROM_ALL)