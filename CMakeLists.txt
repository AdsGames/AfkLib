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
find_library(ALLEGRO_LIBRARY NAMES liballegro.dll.a liballegro.so liballegro.5.2.dylib REQUIRED)
find_library(ALLEGRO_ACODEC_LIBRARY NAMES liballegro_acodec.dll.a liballegro_acodec.so liballegro_acodec.5.2.dylib REQUIRED)
find_library(ALLEGRO_AUDIO_LIBRARY NAMES liballegro_audio.dll.a liballegro_audio.so liballegro_audio.5.2.dylib REQUIRED)
find_library(ALLEGRO_COLOR_LIBRARY NAMES liballegro_color.dll.a liballegro_color.so liballegro_color.5.2.dylib REQUIRED)
find_library(ALLEGRO_DIALOG_LIBRARY NAMES liballegro_dialog.dll.a liballegro_dialog.so liballegro_dialog.5.2.dylib REQUIRED)
find_library(ALLEGRO_FONT_LIBRARY NAMES liballegro_font.dll.a liballegro_font.so liballegro_font.5.2.dylib REQUIRED)
find_library(ALLEGRO_IMAGE_LIBRARY NAMES liballegro_image.dll.a liballegro_image.so liballegro_image.5.2.dylib REQUIRED)
find_library(ALLEGRO_MAIN_LIBRARY NAMES liballegro_main.dll.a liballegro_main.so liballegro_main.5.2.dylib REQUIRED)
find_library(ALLEGRO_PRIMITIVES_LIBRARY NAMES liballegro_primitives.dll.a liballegro_primitives.so liballegro_primitives.5.2.dylib REQUIRED)
find_library(ALLEGRO_TTF_LIBRARY NAMES liballegro_ttf.dll.a liballegro_ttf.so liballegro_ttf.5.2.dylib REQUIRED)

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
if (WIN32)
    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
            ARCHIVE  DESTINATION C:/msys64/mingw32/lib
            LIBRARY  DESTINATION C:/msys64/mingw32/lib
            RUNTIME  DESTINATION C:/msys64/mingw32/bin)

    install(DIRECTORY include/ DESTINATION C:/msys64/mingw32/include/${PROJECT_NAME})

    install(EXPORT ${PROJECT_NAME} DESTINATION C:/msys64/mingw32/share/${PROJECT_NAME}/cmake)
    export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}.cmake)
else(WIN32)
    include(GNUInstallDirs)

    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

    install(EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
    export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}.cmake)
endif(WIN32)