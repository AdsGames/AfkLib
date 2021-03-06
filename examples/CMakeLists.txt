cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include dir
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/bin)

# Find libs
if(!EMSCRIPTEN)
  find_library(SDL_LIBRARY NAMES libSDL2 REQUIRED)
  find_library(SDL_MIXER_LIBRARY NAMES libSDL2_mixer REQUIRED)
  find_library(SDL_IMAGE_LIBRARY NAMES libSDL2_image REQUIRED)
  find_library(SDL_TTF_LIBRARY NAMES libSDL2_ttf REQUIRED)
  find_library(SDL_GFX_LIBRARY NAMES libSDL2_gfx REQUIRED)
  find_library(SDL_MAIN_LIBRARY NAMES libSDL2main REQUIRED)
  find_library(AFK_LIBRARY NAMES libafk PATHS ${CMAKE_BINARY_DIR}/lib REQUIRED NO_DEFAULT_PATH)
endif(!EMSCRIPTEN)


# Build examples
set(EXAMPLES ex_display ex_sprite ex_button ex_message_box ex_fps ex_keyboard ex_mouse ex_sound)

foreach(EX_NAME ${EXAMPLES})
  add_executable(${EX_NAME} ${CMAKE_CURRENT_LIST_DIR}/${EX_NAME}.cpp)
  target_compile_options(${EX_NAME} PRIVATE -Wall -Wextra -pedantic -Wno-unused-parameter)
    
  # Emscripten support
  if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_compile_options(${EX_NAME} PUBLIC -sWASM=1 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sUSE_SDL_MIXER=2 -sUSE_SDL_GFX=2 -sSDL2_IMAGE_FORMATS=["png"]  -sDISABLE_EXCEPTION_CATCHING=0 -sSAFE_HEAP=1)
    target_link_libraries(${EX_NAME} -sUSE_SDL=2 afk)
    set_target_properties(${EX_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_CURRENT_LIST_DIR}/assets --use-preload-plugins")

  # Run of the mill executable
  else(EMSCRIPTEN)
    if(MINGW)
      target_link_libraries(${EX_NAME} -lmingw32)
    endif(MINGW)
    target_link_libraries(${EX_NAME} -lm ${SDL_MAIN_LIBRARY} ${SDL_LIBRARY} ${SDL_MIXER_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL_GFX_LIBRARY} afk)
  endif(EMSCRIPTEN)
endforeach()

# Export assets
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/bin/assets/)
