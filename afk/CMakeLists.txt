cmake_minimum_required(VERSION 3.16)

project (afk
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

# Lib
add_library(${PROJECT_NAME} 
  STATIC 
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} 
  PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${EXTERNAL_INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME} 
  PRIVATE 
    -Wall 
    -Wextra
    -pedantic 
)

set_target_properties(${PROJECT_NAME} 
  PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Emscripten specific options
if(EMSCRIPTEN) 
  target_compile_options(${PROJECT_NAME} 
    PRIVATE
      -sUSE_SDL=2
      -sUSE_SDL_IMAGE=2
      -sUSE_SDL_TTF=2
      -sUSE_SDL_MIXER=2
      -sUSE_SDL_GFX=2
  )

  set(EXTERNAL_INCLUDE_LIBS ${EXTERNAL_INCLUDE_LIBS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sUSE_SDL_MIXER=2 -sUSE_SDL_GFX=2)
endif(EMSCRIPTEN)

# Link link libraries
include(${EXTERNAL_DIR}/libs.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTERNAL_INCLUDE_LIBS})

# Install info
IF(MINGW)
  get_filename_component(BINARY_PATH ${CMAKE_C_COMPILER} PATH)
  set(CMAKE_INSTALL_PREFIX ${BINARY_PATH}/..)
endif(MINGW)

include(GNUInstallDirs)

message(STATUS "Lib install directory set to ${CMAKE_INSTALL_PREFIX}")
 
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)

install(
  DIRECTORY include/ 
  DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/${PROJECT_NAME}
)

install(
  EXPORT ${PROJECT_NAME} 
  DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
  FILES ${EXTERNAL_DIR}/${PROJECT_NAME}-config.cmake
  DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}
)
