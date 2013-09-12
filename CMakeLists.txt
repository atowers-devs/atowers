SET (PROJECT_NAME "atowers")

project (${PROJECT_NAME})
cmake_minimum_required (VERSION 2.8)

find_package (SDL REQUIRED)
find_package (SDL_image REQUIRED)

link_libraries (
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY}
  SDLmain
)

file (GLOB_RECURSE ATOWERS_SOURCES "src/*.cpp")
file (GLOB_RECURSE ATOWERS_INCLUDES "src/*.hpp")

include_directories (ATOWERS_INCLUDES)
add_executable (${PROJECT_NAME} ${ATOWERS_SOURCES})
target_link_libraries (${PROJECT_NAME} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
