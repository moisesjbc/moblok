#!/bin/bash
# build-packages.sh : Builds a DEB package from sources using CMake and CPack.

# We are about to change the current directory, so we save the current one for
# returning.
old_directory=`pwd`

# Go to repository toplevel directory (aka. the parent directory of this 
# script's dir.
cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../"

# Remove cmake and CPack build files for forcing a rebuild.
rm -r CMakeCache.txt _CPack_Packages CPackSourceConfig.cmake CPackConfig.cmake cmake_install.cmake CMakeFiles/ *.deb

# Build the packages.
cmake .
make package

# Refine the generated DEB so lintian doesn't throw any errors.
./scripts/refine-deb.sh

# Return to the directory from where this script was invoked.
cd "$old_directory"

# References
###############################################################################
# Can a Bash script tell what directory it's stored in?
# http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
###############################################################################
