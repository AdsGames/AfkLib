cmake_minimum_required(VERSION 3.14)

include(${EXTERNAL_DIR}/libs.cmake)

# Add include dir
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/build)

# Config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(EXAMPLES ex_display ex_sprite ex_rotate ex_fps ex_mouse ex_physics ex_sound ex_particles ex_keyboard ex_collision ex_message_box)

# Build examples
foreach(EX_NAME ${EXAMPLES})
  add_executable(${EX_NAME} 
    ${CMAKE_CURRENT_LIST_DIR}/src/${EX_NAME}.cpp
  )

  target_compile_options(${EX_NAME} 
    PRIVATE 
      -O2 
      -Wall
      -Wextra 
      -pedantic 
      -Wno-unused-parameter
    )

  set_target_properties(${EX_NAME} 
    PROPERTIES 
      CXX_STANDARD 17 
      CXX_STANDARD_REQUIRED ON
  )

  # Emscripten support
  if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_compile_options(${EX_NAME}
      PRIVATE
        -sUSE_SDL=2
        -sUSE_SDL_IMAGE=2
        -sUSE_SDL_TTF=2
        -sUSE_SDL_MIXER=2
        -sUSE_SDL_GFX=2
        -sSDL2_IMAGE_FORMATS=["png"]
    )

    target_link_libraries(${EX_NAME}
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
      imported::entt
      afk
    )

    set_target_properties(${EX_NAME}
      PROPERTIES
        LINK_FLAGS "--preload-file ${CMAKE_CURRENT_LIST_DIR}/assets@/assets --use-preload-plugins"
    )

  # Run of the mill executable
  else(EMSCRIPTEN)
    if(MINGW)
      target_link_libraries(${EX_NAME} -lmingw32)
    endif(MINGW)

    target_link_libraries(${EX_NAME}
      -lm
      SDL2::Main
      SDL2::Image
      SDL2::Mixer
      SDL2::TTF
      SDL2::GFX
      EnTT::EnTT
      afk
    )
  endif(EMSCRIPTEN)
endforeach()

# Export assets
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)
