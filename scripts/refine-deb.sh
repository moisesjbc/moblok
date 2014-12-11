#!/bin/bash
# refine-deb.sh

SOURCE_DEB="moblok-1-0-0.x86_64.deb"
DST_DEB=$SOURCE_DEB

# We are about to change the current directory, so we save the current one for
# returning.
old_directory=`pwd`

# Go to repository toplevel directory (aka. the parent directory of this 
# script's dir.
cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../"

# Uncompress the deb package in a temp dir.
rm -r .tmp
mkdir -p .tmp/DEBIAN
dpkg -x $SOURCE_DEB .tmp
dpkg --control $SOURCE_DEB .tmp/DEBIAN

# Include changelog file.
mkdir -p .tmp/usr/share/doc/moblok
gzip -9 --keep debian/changelog
cp debian/changelog.gz .tmp/usr/share/doc/moblok/changelog.Debian.gz

# Include copyright file.
cp debian/copyright .tmp/usr/share/doc/moblok/copyright

# Include control file.
DEB_SOFTWARE_NAME="moblok"
DEB_MAJOR_VERSION="1"
DEB_MINOR_VERSION="0"
DEB_REVISION="1"

echo "Package: $DEB_SOFTWARE_NAME
Version: $DEB_MAJOR_VERSION.$DEB_MINOR_VERSION-$DEB_REVISION
Section: games
Priority: optional
Architecture: amd64
Depends: libc6, fonts-liberation, libsdl2-2.0-0, libsdl2-mixer-2.0-0, libsdl2-image-2.0-0, libsdl2-ttf-2.0-0
Maintainer: Moisés J. Bonilla Caraballo <moisesjbc@gmail.com>
Description: Just another tetris clone.
 Moblok' is a clone of the famous game Tetris.
" > ".tmp/DEBIAN/control"

# Compress the deb package again.
fakeroot dpkg-deb --build .tmp $DST_DEB

#dpkg -b .tmp moblok-cool.deb

# Return to the directory from where this script was invoked.
cd "$old_directory"

# References
###############################################################################
# Modify dependencies, add/remove files of debian(.deb) package
# http://geekwentfreak-raviteja.rhcloud.com/blog/2012/10/10/modify-dependencies-addremove-files-of-debian-deb-package/
###############################################################################
