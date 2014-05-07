# Create a named project
set( PROJECT_NAME moblok )
project( moblok )
cmake_minimum_required( VERSION 2.8 )

# Set the version number.
set( ${PROJECT_NAME}_VERSION_MAJOR 0 )
set( ${PROJECT_NAME}_VERSION_MINOR 7 )
set( ${PROJECT_NAME}_VERSION_PATCH 1 )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/source/include/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/source/include/config.hpp )

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
message( STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}" )

# Install
install( TARGETS ${PROJECT_NAME} DESTINATION bin )
install( DIRECTORY ${CMAKE_HOME_DIRECTORY}/share/moblok DESTINATION share )

#<----snip your usual build instructions snip--->
set( CPACK_PACKAGE_VERSION ${VERSION} )
set( CPACK_GENERATOR "DEB" ) # TODO: RPM and anything else?
set( CPACK_PACKAGE_NAME "Moblok'" )
set( CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR} )
set( CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH} )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Just another tetris clone." )
set( CPACK_PACKAGE_CONTACT "Moisés J. Bonilla Caraballo <moisesjbc@gmail.com>" )
set( CPACK_PACKAGE_VENDOR "Moisés J. Bonilla Caraballo" )

set( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_HOME_DIRECTORY}/README.md" )
#set( CPACK_RESOURCE_FILE_LICENSE “${CMAKE_HOME_DIRECTORY}/COPYING” )

set( CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} )
set( CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}-${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}.${CMAKE_SYSTEM_PROCESSOR} )

if( UNIX )
#DEB
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Moisés J. Bonilla Caraballo <moisesjbc@gmail.com>" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl1.2debian (>= 1.2), libsdl-mixer1.2 (>= 1.2), libsdl-image1.2 (>= 1.2), g++ (>= 4.6), cmake (>= 2.8)" )
set( CPACK_DEBIAN_PACKAGE_SECTION "games" )

#RPM
#set( CPACK_RPM_PACKAGE_REQUIRES "libsdl1.2 (>= 1.2), libsdl-mixer1.2 (>= 1.2), libsdl-image1.2 (>= 1.2), g++ (>= 4.6), cmake (>= 2.8)" )
endif( UNIX )

include(CPack)
