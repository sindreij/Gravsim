cmake_minimum_required (VERSION 2.6)
project (Gravsim)

# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package (SDL REQUIRED)
Find_Package (SDL_image REQUIRED) # if using SDL_image
Find_Package (SDL_ttf REQUIRED)

include_directories(${SDL_INCLUDE_DIR} 
  ${SDLTTF_INCLUDE_DIR} 
  ${SDLIMAGE_INCLUDE_DIR})

set_source_files_properties(planets.cpp engine.cpp objects.cpp states.cpp COMPILE_FLAGS -ggdb)

add_executable (Gravsim planets.cpp engine.cpp objects.cpp states.cpp)

target_link_libraries(Gravsim 
  ${OPTIONAL_LIBS} 
  ${SDL_LIBRARY} 
  ${SDLTTF_LIBRARY} 
  ${SDLIMAGE_LIBRARY}
  SDL_gfx)
