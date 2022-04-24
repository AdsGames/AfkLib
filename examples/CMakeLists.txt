cmake_minimum_required(VERSION 3.14)

project (examples 
  VERSION 1.0.0
  LANGUAGES CXX
)

include(${EXTERNAL_DIR}/libs.cmake)


# Config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXAMPLES ex_display ex_sprite ex_rotate ex_fps ex_mouse ex_physics ex_sound ex_particles ex_keyboard ex_collision ex_message_box)

# Build examples
foreach(EX_NAME ${EXAMPLES})
  add_executable(${EX_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/${EX_NAME}.cpp)

  target_compile_options(${EX_NAME} 
    PRIVATE 
      -Wall 
      -Wextra
      -pedantic
      -Wno-unused-parameter
  )

  # Emscripten support
  if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set_target_properties(${EX_NAME}
      PROPERTIES
      LINK_FLAGS 
      "--preload-file ${CMAKE_CURRENT_LIST_DIR}/assets@/assets --use-preload-plugins -s DEMANGLE_SUPPORT=1 -s DISABLE_EXCEPTION_CATCHING=0 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_GFX=2 -s SDL2_IMAGE_FORMATS=[\"png\"]"
    )

    target_link_libraries(${EX_NAME} imported::entt afk)

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
