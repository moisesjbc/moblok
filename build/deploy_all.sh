#!/bin/bash
TARGET=moblok
VERSION=v0.7.1-beta
DATA_DIR=data
RELEASES_DIR=../../releases

# TODO: Move moblok.exe from release/ to ../

# Remove all previous releases.
rm -r "$RELEASES_DIR"/*

# Get a list of platforms for building to.
platforms=`ls bin`

for platform in $platforms
do
	SOURCE_DIR="bin/$platform"
	if [[ -d "$SOURCE_DIR" ]] ; then
		printf "Found plataform: [%s]\n" "$SOURCE_DIR"

		RELEASE="$TARGET-$VERSION-$platform"
		TARGET_DIR="$RELEASES_DIR/$RELEASE"
		printf "Directory: [%s]\n" $TARGET_DIR

		# Create the release directory.
		printf "Creating target directory: [%s] ...\n" $TARGET_DIR
		mkdir "$TARGET_DIR"
		printf "Creating target directory: [%s] ...OK\n" $TARGET_DIR

		# Copy the data directory to the target dir.
		printf "Copying data dir ...\n"
		cp -r $DATA_DIR $TARGET_DIR
		printf "Copying data dir ...OK\n"

		# Copy the libraries to the target dir.
		echo "find $SOURCE_DIR/" ! -name Makefile*
		find "$SOURCE_DIR/" \( -name "moblok*" -o -name "*.dll" -o -name "*.so" -o -name "*.exe" \) -exec cp '{}' "$TARGET_DIR" \;

		# Go to releases directory (save the current directory for return).
		OLD_DIR=`pwd`
		cd "$RELEASES_DIR"

		# Compress the release.
		if [[ $RELEASE == *windows* ]] ; then
			zip -r "$RELEASE.zip" "$RELEASE"
		else
			tar -zcvf "$RELEASE.tar.gz" "$RELEASE"
		fi

		# Return to previous directory.
		cd "$OLD_DIR"
	fi
done
