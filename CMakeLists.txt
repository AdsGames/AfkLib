cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project (afk VERSION 1.0.0 LANGUAGES CXX)

# Add sources
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

# Create lib
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE -O2 -Wall -Wextra -pedantic)
 
# Add include
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# Versioning
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)

# Find libs

if(EMSCRIPTEN)
  set(EnTT_DIR "C:/Users/alege/Documents/GitHub/emsdk/upstream/lib/cmake/EnTT")
  find_package(EnTT REQUIRED)

else(EMSCRIPTEN)
  find_package(EnTT REQUIRED)
  find_library(SDL_LIBRARY NAMES SDL2 REQUIRED)
  find_library(SDL_MIXER_LIBRARY NAMES SDL2_mixer REQUIRED)
  find_library(SDL_IMAGE_LIBRARY NAMES SDL2_image REQUIRED)
  find_library(SDL_TTF_LIBRARY NAMES SDL2_ttf REQUIRED)
  find_library(SDL_GFX_LIBRARY NAMES SDL2_gfx REQUIRED)
  find_library(SDL_MAIN_LIBRARY NAMES SDL2main REQUIRED)
endif(EMSCRIPTEN)

# Emscripten specific options
if(EMSCRIPTEN) 
  target_compile_options(
    ${PROJECT_NAME}
    PRIVATE  
    -sUSE_SDL=2 
    -sUSE_SDL_IMAGE=2 
    -sUSE_SDL_TTF=2 
    -sUSE_SDL_MIXER=2 
    -sUSE_SDL_GFX=2 
    -sSDL2_IMAGE_FORMATS=["png"]
  )
  target_link_libraries(
    ${PROJECT_NAME} 
    -sWASM=1 
    -sUSE_SDL=2
    -sUSE_SDL_IMAGE=2 
    -sUSE_SDL_TTF=2 
    -sUSE_SDL_MIXER=2 
    -sUSE_SDL_GFX=2 
    -sSDL2_IMAGE_FORMATS=["png"]
    -sDEMANGLE_SUPPORT=1
    EnTT::EnTT
  )
  target_link_libraries(${PROJECT_NAME} -sUSE_SDL=2 -fsanitize=address)

# All other system options
else(EMSCRIPTEN)
  target_link_libraries(
    ${PROJECT_NAME} 
    ${SDL_LIBRARY} 
    ${SDL_MIXER_LIBRARY} 
    ${SDL_IMAGE_LIBRARY} 
    ${SDL_TTF_LIBRARY} 
    ${SDL_GFX_LIBRARY} 
    ${SDL_MAIN_LIBRARY} 
    EnTT::EnTT
  )
endif(EMSCRIPTEN)

# Install info
if (EMSCRIPTEN)
  get_filename_component(EMSDK_DIR ${CMAKE_TOOLCHAIN_FILE} DIRECTORY)
  set(EMSDK_DIR ${EMSDK_DIR}/../../../system)
  message("Lib install directory set to ${EMSDK_DIR}")

  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${EMSDK_DIR}/lib
  LIBRARY DESTINATION ${EMSDK_DIR}/lib
  RUNTIME DESTINATION ${EMSDK_DIR}/bin)

  install(DIRECTORY include/ DESTINATION ${EMSDK_DIR}/include/${PROJECT_NAME})

# Msys2 specific
elseif (WIN32)
  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
          ARCHIVE DESTINATION C:/msys64/mingw32/lib
          LIBRARY DESTINATION C:/msys64/mingw32/lib
          RUNTIME DESTINATION C:/msys64/mingw32/bin)

  install(DIRECTORY include/ DESTINATION C:/msys64/mingw32/include/${PROJECT_NAME})

  install(EXPORT ${PROJECT_NAME} DESTINATION C:/msys64/mingw32/share/${PROJECT_NAME}/cmake)
  export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}.cmake)

# Linux mac etc.
else()
  include(GNUInstallDirs)

  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
          ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
          LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

  install(EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
  export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}.cmake)
endif()

# Examples
include(${CMAKE_SOURCE_DIR}/examples/CMakeLists.txt)