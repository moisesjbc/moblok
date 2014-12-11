# Create a named project
set( PROJECT_NAME moblok )
project( moblok )
cmake_minimum_required( VERSION 2.8 )

# Set the version number.
set( ${PROJECT_NAME}_VERSION_MAJOR 1 )
set( ${PROJECT_NAME}_VERSION_MINOR 0 )
set( ${PROJECT_NAME}_VERSION_PATCH 0 )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/source/include/config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/source/include/config.hpp )

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

message( STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}" )

# Install in /usr
# Source: http://www.cmake.org/pipermail/cmake/2009-March/027859.html
set( CMAKE_INSTALL_PREFIX /usr )
set( CPACK_SET_DESTDIR "ON" )

# Install
install( TARGETS ${PROJECT_NAME} DESTINATION games )
install( DIRECTORY ${CMAKE_HOME_DIRECTORY}/share/moblok DESTINATION share )

#<----snip your usual build instructions snip--->
set( CPACK_PACKAGE_VERSION ${VERSION} )
set( CPACK_GENERATOR "DEB" ) # TODO: RPM and anything else?
set( CPACK_PACKAGE_NAME "moblok" )
set( CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR} )
set( CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH} )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Just another tetris clone." )
set( CPACK_PACKAGE_CONTACT "Moisés J. Bonilla Caraballo <moisesjbc@gmail.com>" )
set( CPACK_PACKAGE_VENDOR "Moisés J. Bonilla Caraballo" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Just another tetris clone." )

set( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md" )

set( CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} )
set( CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}-${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}.${CMAKE_SYSTEM_PROCESSOR} )

if( UNIX )
#DEB
set( CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, fonts-liberation, libsdl2-2.0-0, libsdl2-mixer-2.0-0, libsdl2-image-2.0-0, libsdl2-ttf-2.0-0" )
set( CPACK_DEBIAN_PACKAGE_SECTION "games" )
endif( UNIX )

include(CPack)

# Uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
