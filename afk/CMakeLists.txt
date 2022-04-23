cmake_minimum_required(VERSION 3.14)

project (afk 
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

include(${EXTERNAL_DIR}/libs.cmake)

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
)

target_compile_options(${PROJECT_NAME} 
  PRIVATE 
    -O2 
    -Wall 
    -Wextra
    -pedantic
)

set_target_properties(${PROJECT_NAME} 
  PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
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
      -sSDL2_IMAGE_FORMATS=["png"]
  )

  target_link_libraries(${PROJECT_NAME} 
    -sWASM=1 
    -sUSE_SDL=2
    -sUSE_SDL_IMAGE=2 
    -sUSE_SDL_TTF=2 
    -sUSE_SDL_MIXER=2 
    -sUSE_SDL_GFX=2 
    -sSDL2_IMAGE_FORMATS=["png"]
    -sDEMANGLE_SUPPORT=1
    imported::entt
  )

  target_link_libraries(${PROJECT_NAME} 
    -sUSE_SDL=2 
    -fsanitize=address
  )

# All other system options
else(EMSCRIPTEN)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC
      SDL2::Image
      SDL2::Mixer
      SDL2::TTF
      SDL2::GFX
      SDL2::Main
      imported::entt
  )
endif(EMSCRIPTEN)

# Install info
if (EMSCRIPTEN)
  get_filename_component(EMSDK_DIR ${CMAKE_TOOLCHAIN_FILE} DIRECTORY)
  set(EMSDK_DIR ${EMSDK_DIR}/../../../system)
  message(STATUS "Lib install directory set to ${EMSDK_DIR}")

  set(CMAKE_INSTALL_LIBDIR ${EMSDK_DIR}/lib)
  set(CMAKE_INSTALL_BINDIR ${EMSDK_DIR}/bin)
  set(CMAKE_INSTALL_INCLUDEDIR ${EMSDK_DIR}/include)
  set(CMAKE_INSTALL_DATAROOTDIR ${EMSDK_DIR}/share)

elseif (WIN32)
  get_filename_component(WIN32_BIN_PATH ${CMAKE_C_COMPILER} PATH)
  set(WIN32_DIR ${WIN32_BIN_PATH}/../)
  message(STATUS "Lib install directory set to ${WIN32_DIR}")

  set(CMAKE_INSTALL_LIBDIR ${WIN32_DIR}/lib)
  set(CMAKE_INSTALL_BINDIR  ${WIN32_DIR}/bin)
  set(CMAKE_INSTALL_INCLUDEDIR ${WIN32_DIR}/include)
  set(CMAKE_INSTALL_DATAROOTDIR ${WIN32_DIR}/share)
else()
  include(GNUInstallDirs)
endif()

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
  DIRECTORY include/ 
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(
  EXPORT ${PROJECT_NAME} 
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

export(
  TARGETS ${PROJECT_NAME} 
  FILE ${PROJECT_NAME}.cmake
)