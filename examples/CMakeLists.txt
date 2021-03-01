cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include dir
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/bin)

# Find libs
find_library(ALLEGRO_LIBRARY NAMES liballegro REQUIRED)
find_library(ALLEGRO_ACODEC_LIBRARY NAMES liballegro_acodec REQUIRED)
find_library(ALLEGRO_AUDIO_LIBRARY NAMES liballegro_audio REQUIRED)
find_library(ALLEGRO_COLOR_LIBRARY NAMES liballegro_color REQUIRED)
find_library(ALLEGRO_DIALOG_LIBRARY NAMES liballegro_dialog REQUIRED)
find_library(ALLEGRO_FONT_LIBRARY NAMES liballegro_font REQUIRED)
find_library(ALLEGRO_IMAGE_LIBRARY NAMES liballegro_image REQUIRED)
find_library(ALLEGRO_MAIN_LIBRARY NAMES liballegro_main REQUIRED)
find_library(ALLEGRO_PRIMITIVES_LIBRARY NAMES liballegro_primitives REQUIRED)
find_library(ALLEGRO_TTF_LIBRARY NAMES liballegro_ttf REQUIRED)

# Build examples
set(EXAMPLES ex_display ex_sprite ex_button ex_message_box ex_fps)

foreach(EX_NAME ${EXAMPLES})
  add_executable(${EX_NAME} ${CMAKE_CURRENT_LIST_DIR}/${EX_NAME}.cpp)
  target_compile_options(${EX_NAME} PRIVATE -Wall -Wextra -pedantic)
  target_link_libraries(${EX_NAME} ${ALLEGRO_LIBRARY} ${ALLEGRO_TTF_LIBRARY} ${ALLEGRO_PRIMITIVES_LIBRARY} ${ALLEGRO_ACODEC_LIBRARY} ${ALLEGRO_AUDIO_LIBRARY} ${ALLEGRO_COLOR_LIBRARY} ${ALLEGRO_DIALOG_LIBRARY} ${ALLEGRO_FONT_LIBRARY} ${ALLEGRO_MAIN_LIBRARY} ${ALLEGRO_IMAGE_LIBRARY} afk)
endforeach()

# Export assets
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/bin/assets/)
