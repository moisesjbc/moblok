# Create a named project
set( PROJECT_NAME moblok )
project( moblok )
cmake_minimum_required( VERSION 2.8 )

# Set the version number.
set( PROJECT_VERSION_MAJOR 1 )
set( PROJECT_VERSION_MINOR 0 )
set( PROJECT_VERSION_PATCH 0 )

# Add sources
file( GLOB ${PROJECT_NAME}_INCLUDES source/include/*.hpp )
file( GLOB ${PROJECT_NAME}_SOURCES source/src/*.cpp )

# Load SDL
INCLUDE( FindPkgConfig )
PKG_SEARCH_MODULE( SDL2 REQUIRED sdl2 )
PKG_SEARCH_MODULE( SDL2IMAGE REQUIRED SDL2_image>=2.0.0 )
PKG_SEARCH_MODULE( SDL2MIXER REQUIRED SDL2_mixer>=2.0.0 )
PKG_SEARCH_MODULE( SDL2TTF REQUIRED SDL2_ttf>=2.0.0 )

# Include directories
include_directories( source/include )

# Compiler flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -s -ansi -Werror -pedantic -pedantic-errors -std=c++0x" )

# Executable
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_INCLUDES} )

message ( "SDL2_LIBRARY: = ${PROJECT_NAME}:${${PROJECT_NAME}_SOURCES}:${${PROJECT_NAME}_INCLUDES}")

# Target libraries
target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} )
target_link_libraries (${PROJECT_NAME} ${SDL2IMAGE_LIBRARIES} )
target_link_libraries (${PROJECT_NAME} ${SDL2MIXER_LIBRARIES} )
target_link_libraries (${PROJECT_NAME} ${SDL2TTF_LIBRARIES} )
# TODO: Add dependencies "Liberation*ttf" and libc6.

message( STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}" )

# Install in /usr
# Source: http://www.cmake.org/pipermail/cmake/2009-March/027859.html
set( CMAKE_INSTALL_PREFIX /usr )
set( CPACK_SET_DESTDIR "ON" )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/source/include/config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/source/include/config.hpp )

# Install
install( TARGETS ${PROJECT_NAME} DESTINATION games )
install( DIRECTORY ${CMAKE_HOME_DIRECTORY}/share/moblok DESTINATION share )

# Package building
if( UNIX )
# DEB package
configure_file(
    ./scripts/config.in
    ./scripts/config )
add_custom_target(
    deb
    COMMAND ./scripts/build-deb.sh )
add_dependencies( deb ${PROJECT_NAME} )
endif( UNIX )

# Uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
