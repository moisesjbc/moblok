#!/bin/bash
# refine-deb.sh

# We are about to change the current directory, so we save the current one for
# returning.
old_directory=`pwd`

# Go to repository toplevel directory (aka. the parent directory of this 
# script's dir.
cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../"

# Load configuration file.
source scripts/config

# Set package's name.
ARCH=`uname -p`
DST_DEB="${PROJECT_NAME}_${PACKAGE_MAJOR_VERSION}.${PACKAGE_MINOR_VERSION}.${PACKAGE_PATCH_VERSION}-${PACKAGE_REVISION}_${ARCH}.deb"
TMP_DEB_DIR=".tmp"

# Create a temporal dir for the debian package.
rm -r $TMP_DEB_DIR
mkdir -p $TMP_DEB_DIR/DEBIAN
mkdir -p $TMP_DEB_DIR/usr

# Copy the dir "share" to temporal DEB dir.
cp -R share $TMP_DEB_DIR/usr

# Copy the executable to DEB dir.
mkdir -p $TMP_DEB_DIR/usr/games
cp moblok $TMP_DEB_DIR/usr/games

# Include changelog file.
mkdir -p .tmp/usr/share/doc/moblok
gzip -9 --keep debian/changelog
cp debian/changelog.gz .tmp/usr/share/doc/moblok/changelog.Debian.gz

# Include copyright file.
cp debian/copyright .tmp/usr/share/doc/moblok/copyright

# Set the desktop file for the game.
mkdir .tmp/usr/share/applications
cp debian/moblok.desktop .tmp/usr/share/applications

# Include control file.
DEB_INSTALED_SIZE=`du -s .tmp | cut -f1`

echo "Package: $PROJECT_NAME
Version: $PACKAGE_MAJOR_VERSION.$PACKAGE_MINOR_VERSION.$PACKAGE_PATCH_VERSION-$PACKAGE_REVISION
Section: games
Priority: optional
Architecture: amd64
Depends: libc6, fonts-liberation, libsdl2-2.0-0, libsdl2-mixer-2.0-0, libsdl2-image-2.0-0, libsdl2-ttf-2.0-0
Maintainer: Moisés J. Bonilla Caraballo <moisesjbc@gmail.com>
Installed-Size: $DEB_INSTALED_SIZE
Description: Just another tetris clone.
 Moblok' is a clone of the famous game Tetris.
" > ".tmp/DEBIAN/control"

# Change permissions to the standar expected by lintian.
chmod 0755 .tmp/usr/
chmod 0755 .tmp/usr/share/
chmod 0755 .tmp/usr/games/
chmod 0755 .tmp/usr/share/applications
chmod 0755 .tmp/usr/share/doc/
chmod 0755 .tmp/usr/share/doc/moblok/
chmod 0644 .tmp/usr/share/doc/moblok/changelog.Debian.gz
chmod 0644 .tmp/usr/share/doc/moblok/copyright
chmod 0644 .tmp/usr/share/applications/moblok.desktop

# Remove file "md5sums" so it will be regenerated when rebuilding package.
rm .tmp/DEBIAN/md5sums

# Compress the deb package.
fakeroot dpkg-deb --build .tmp $DST_DEB

# Return to the directory from where this script was invoked.
cd "$old_directory"

# References
###############################################################################
# Modify dependencies, add/remove files of debian(.deb) package
# http://geekwentfreak-raviteja.rhcloud.com/blog/2012/10/10/modify-dependencies-addremove-files-of-debian-deb-package/
#
# Check folder size in bash
# http://stackoverflow.com/questions/16661982/check-folder-size-in-bash
###############################################################################
