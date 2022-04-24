cmake_minimum_required(VERSION 3.14)

project (afk 
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    PUBLIC
      -sUSE_SDL=2
      -sUSE_SDL_IMAGE=2
      -sUSE_SDL_TTF=2
      -sUSE_SDL_MIXER=2
      -sUSE_SDL_GFX=2
      -sSDL2_IMAGE_FORMATS=["png"]
  )

  set(SDL2_LIBRARIES "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_GFX=2")

# All other system options
else(EMSCRIPTEN)
  set(SDL2_LIBRARIES "SDL2::Image SDL2::Mixer SDL2::TTF SDL2::GFX SDL2::Main")
endif(EMSCRIPTEN)

# Link link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} imported::entt)

# Install info
if (EMSCRIPTEN OR WIN32)
  if (EMSCRIPTEN)
    get_filename_component(EMSDK_DIR ${CMAKE_TOOLCHAIN_FILE} DIRECTORY)
    set(BASE_DIR ${EMSDK_DIR}/../../../system)
  elseif (WIN32)
    get_filename_component(WIN32_BIN_PATH ${CMAKE_C_COMPILER} PATH)
    set(BASE_DIR ${WIN32_BIN_PATH}/..)
  endif(EMSCRIPTEN)

  message(STATUS "Lib install directory set to ${BASE_DIR}")

  set(CMAKE_INSTALL_LIBDIR ${BASE_DIR}/lib)
  set(CMAKE_INSTALL_BINDIR ${BASE_DIR}/bin)
  set(CMAKE_INSTALL_INCLUDEDIR ${BASE_DIR}/include)
  set(CMAKE_INSTALL_DATAROOTDIR ${BASE_DIR}/share)
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