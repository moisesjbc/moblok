# Create a named project
set( PROJECT_NAME moblok )
project(moblok)
cmake_minimum_required(VERSION 2.8)

# Set the version number.
set (moblok_VERSION_MAJOR 0)
set (moblok_VERSION_MINOR 7)
set (moblok_VERSION_VERSION 1)

# Add sources
file( GLOB ${PROJECT_NAME}_INCLUDES source/include/*.hpp )
file( GLOB ${PROJECT_NAME}_SOURCES source/src/*.cpp )

# Load SDL
find_package( SDL REQUIRED )
find_package( SDL_image REQUIRED )
find_package( SDL_mixer REQUIRED )

# Include directories
include_directories( source/include )

# Compiler flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -Werror -pedantic -pedantic-errors -std=c++0x" )

# Executable
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_INCLUDES} )

# Target libraries
target_link_libraries (${PROJECT_NAME} ${SDL_LIBRARY} )
target_link_libraries (${PROJECT_NAME} ${SDLIMAGE_LIBRARY} )
target_link_libraries (${PROJECT_NAME} ${SDLMIXER_LIBRARY} )

message( STATUS "${SDL_LIBRARY}" )

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
