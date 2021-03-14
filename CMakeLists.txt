cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project (afk VERSION 1.0.0 LANGUAGES CXX)

# Add sources
file(GLOB_RECURSE SOURCES ${CMAKE_BINARY_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_BINARY_DIR}/include/*.h)

# Create lib
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE -O2 -Wall -Wextra -pedantic)

# Add include
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# Versioning
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)

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
    )
    target_link_libraries(${PROJECT_NAME} -sUSE_SDL=2 -fsanitize=address)
else(EMSCRIPTEN)
    # Find libs
    find_library(SDL_LIBRARY NAMES SDL2 REQUIRED)
    find_library(SDL_MIXER_LIBRARY NAMES SDL2_mixer REQUIRED)
    find_library(SDL_IMAGE_LIBRARY NAMES SDL2_image REQUIRED)
    find_library(SDL_TTF_LIBRARY NAMES SDL2_ttf REQUIRED)
    find_library(SDL_GFX_LIBRARY NAMES SDL2_gfx REQUIRED)
    find_library(SDL_MAIN_LIBRARY NAMES SDL2main REQUIRED)

    # Link Libs
    target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY} ${SDL_MIXER_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL_GFX_LIBRARY} ${SDL_MAIN_LIBRARY})
endif(EMSCRIPTEN) 

# Install info
if (EMSCRIPTEN)
    if (NOT CMAKE_TOOLCHAIN_FILE)
        message("CMAKE_TOOLCHAIN_FILE not provided, can not automatically install")
    else()
        get_filename_component(EMSDK_DIR ${CMAKE_TOOLCHAIN_FILE} DIRECTORY)
        set(EMSDK_DIR ${EMSDK_DIR}/../../../system)
        message("Lib install directory set to ${EMSDK_DIR}")

        install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
        ARCHIVE DESTINATION ${EMSDK_DIR}/lib
        LIBRARY DESTINATION ${EMSDK_DIR}/lib
        RUNTIME DESTINATION ${EMSDK_DIR}/bin)

        install(DIRECTORY include/ DESTINATION ${EMSDK_DIR}/include/${PROJECT_NAME})
    endif()
elseif (WIN32)
    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
            ARCHIVE DESTINATION C:/msys64/mingw32/lib
            LIBRARY DESTINATION C:/msys64/mingw32/lib
            RUNTIME DESTINATION C:/msys64/mingw32/bin)

    install(DIRECTORY include/ DESTINATION C:/msys64/mingw32/include/${PROJECT_NAME})

    install(EXPORT ${PROJECT_NAME} DESTINATION C:/msys64/mingw32/share/${PROJECT_NAME}/cmake)
    export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}.cmake)
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
include(${CMAKE_BINARY_DIR}/examples/CMakeLists.txt)