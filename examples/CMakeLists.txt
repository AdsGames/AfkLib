cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include dir
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/bin)

# Find libs
if(!EMSCRIPTEN)
  find_library(SDL_LIBRARY NAMES SDL2 REQUIRED)
  find_library(SDL_MIXER_LIBRARY NAMES SDL2_mixer REQUIRED)
  find_library(SDL_IMAGE_LIBRARY NAMES SDL2_image REQUIRED)
  find_library(SDL_TTF_LIBRARY NAMES SDL2_ttf REQUIRED)
  find_library(SDL_GFX_LIBRARY NAMES SDL2_gfx REQUIRED)
  find_library(SDL_MAIN_LIBRARY NAMES SDL2main REQUIRED)
endif(!EMSCRIPTEN)


# Build examples
set(EXAMPLES ex_display ex_sprite ex_button ex_message_box ex_fps ex_keyboard ex_mouse ex_sound ex_particles ex_rotate)

foreach(EX_NAME ${EXAMPLES})
  add_executable(${EX_NAME} ${CMAKE_CURRENT_LIST_DIR}/${EX_NAME}.cpp)
  target_compile_options(${EX_NAME} PRIVATE -O2 -Wall -Wextra -pedantic -Wno-unused-parameter)
    
  # Emscripten support
  if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_libraries(
      ${EX_NAME} 
      -sWASM=1 
      -sUSE_SDL=2 
      -sUSE_SDL_IMAGE=2 
      -sUSE_SDL_TTF=2 
      -sUSE_SDL_MIXER=2 
      -sUSE_SDL_GFX=2 
      -sSDL2_IMAGE_FORMATS=["png"] 
      -sDEMANGLE_SUPPORT=1
      -sTOTAL_MEMORY=512MB
      -sDISABLE_EXCEPTION_CATCHING=0
      afk
    )
    set_target_properties(${EX_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_CURRENT_LIST_DIR}/assets@/assets --use-preload-plugins")

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
