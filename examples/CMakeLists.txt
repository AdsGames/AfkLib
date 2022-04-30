cmake_minimum_required(VERSION 3.16)

project (examples 
  VERSION 1.0.0
  LANGUAGES CXX
)

# Config
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

  # Emscripten specific options
  if(EMSCRIPTEN) 
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(EXTRA_LIBRARIES 
     "--use-preload-plugins \
      --preload-file ${CMAKE_CURRENT_LIST_DIR}/assets@/assets \
      -s DISABLE_EXCEPTION_CATCHING=0 \
      -s DEMANGLE_SUPPORT=1 \
      -s SDL2_IMAGE_FORMATS=[\"png\"]"
    )
  endif(EMSCRIPTEN)

  # Link libraries 
  if(MINGW)
    target_link_libraries(${EX_NAME} PRIVATE -lmingw32)
  endif(MINGW)
 
  target_link_libraries(${EX_NAME} PRIVATE ${EXTRA_LIBRARIES} afk)
endforeach()

# Export assets
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/examples/assets/)
 