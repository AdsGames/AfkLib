set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${EXTERNAL_DIR}/cmake)


set(EXTERNAL_INCLUDE_DIRS "")
set(EXTERNAL_INCLUDE_LIBS "")

# sdl
if (NOT EMSCRIPTEN)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_mixer REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)
  find_package(SDL2_gfx REQUIRED)
  
  list (APPEND EXTERNAL_INCLUDE_LIBS 
    SDL2::Image 
    SDL2::Mixer 
    SDL2::TTF 
    SDL2::GFX 
    SDL2::Main
  )
  
endif(NOT EMSCRIPTEN)

# entt
find_package(EnTT REQUIRED)

list (APPEND EXTERNAL_INCLUDE_LIBS EnTT::EnTT)
