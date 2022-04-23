set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${EXTERNAL_DIR}/cmake)

# sdl
if (NOT EMSCRIPTEN)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_mixer REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)
  find_package(SDL2_gfx REQUIRED)
endif(NOT EMSCRIPTEN)

# entt
add_library (imported::entt INTERFACE IMPORTED)
set (ENTT_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/lib/entt/single_include)
set_target_properties(imported::entt PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${ENTT_INCLUDE_PATH}")
target_link_libraries(imported::entt INTERFACE EnTT)

list (APPEND EXTERNAL_INCLUDE_DIRS 
  ${ENTT_INCLUDE_PATH}
)