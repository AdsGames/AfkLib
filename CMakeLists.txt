cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (afk VERSION 1.0.0 LANGUAGES CXX)

# Add sources
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# Create lib
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# Add include
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
 
# Versioning
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)

# Find libs
find_library(ALLEGRO_LIBRARY NAMES liballegro)
find_library(ALLEGRO_ACODEC_LIBRARY NAMES liballegro_acodec)
find_library(ALLEGRO_AUDIO_LIBRARY NAMES liballegro_audio)
find_library(ALLEGRO_COLOR_LIBRARY NAMES liballegro_color)
find_library(ALLEGRO_DIALOG_LIBRARY NAMES liballegro_dialog)
find_library(ALLEGRO_FONT_LIBRARY NAMES liballegro_font)
find_library(ALLEGRO_IMAGE_LIBRARY NAMES liballegro_image)
find_library(ALLEGRO_MAIN_LIBRARY NAMES liballegro_main)
find_library(ALLEGRO_PRIMITIVES_LIBRARY NAMES liballegro_primitives)
find_library(ALLEGRO_TTF_LIBRARY NAMES liballegro_ttf)

# Link Libs
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_ACODEC_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_AUDIO_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_COLOR_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_DIALOG_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_FONT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_IMAGE_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_MAIN_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_PRIMITIVES_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_TTF_LIBRARY})



# Install info
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
        ARCHIVE  DESTINATION C:/msys64/mingw32/lib
        LIBRARY  DESTINATION C:/msys64/mingw32/lib
        RUNTIME  DESTINATION C:/msys64/mingw32/bin)

install(DIRECTORY include/ DESTINATION C:/msys64/mingw32/include/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME} DESTINATION C:/msys64/mingw32/share/${PROJECT_NAME}/cmake)
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}.cmake)
