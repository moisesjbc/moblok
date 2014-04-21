TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Give the target executable a name.
CONFIG( debug, debug|release ) {
    TARGET = moblok_debug
} else {
    TARGET = moblok
}

# Set a variable indicating the operative system we are building for.
linux_x86_64{
    OS = linux_x86_64
}windows_x86_64 {
    OS = windows_x86_64
}

# Print a message displaying the target's name and OS.
message( Building target: $$TARGET ($$OS) )

# Set the target and the destination dir according to the current build in use.
# http://stackoverflow.com/questions/2580934/how-to-specify-different-debug-release-output-directories-in-qmake-pro-file
DESTDIR = .

BUILD_DATA_DIR = $$DESTDIR/.build_data/$$TARGET
OBJECTS_DIR = $$BUILD_DATA_DIR/obj
MOC_DIR = $$BUILD_DATA_DIR/moc
RCC_DIR = $$BUILD_DATA_DIR/qrc
UI_DIR = $$BUILD_DATA_DIR/ui

# Libs
LIBS += -lSDL_image -lSDL_mixer `sdl-config --libs` -ljpeg  -lpng -lvorbisfile -lvorbis -logg  -lz -lm

# C++ flags
QMAKE_CXXFLAGS_WARN_ON += -Wall -Werror
QMAKE_CXXFLAGS += `sdl-config --cflags` -pedantic-errors

windows_x86_64 {
    # Withot these options, running the application throws "library not
    # found" errors (libgcc_s_sjlj-1.dll and libstdc++-6.dll)
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

# C++11 support (http://qt-project.org/forums/viewthread/19989)
CONFIG += c++11

HEADERS += \
    ../src/Matrix.hpp \
    ../src/Player.hpp \
    ../src/Tetris.hpp \
    ../src/Game.hpp \
    ../src/Tetromino.hpp

SOURCES += \
    ../src/main.cpp \
    ../src/Matrix.cpp \
    ../src/Player.cpp \
    ../src/Tetris.cpp \
    ../src/Game.cpp
