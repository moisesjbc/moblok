TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL -lSDL_image

# Set the target and the destination dir according to the current build in use.
# http://stackoverflow.com/questions/2580934/how-to-specify-different-debug-release-output-directories-in-qmake-pro-file
DESTDIR = .

CONFIG( debug, debug|release ) {
    TARGET = client_debug
} else {
    TARGET = client_release
}
message( Building target: $$TARGET )

BUILD_DATA_DIR = $$DESTDIR/.build_data/$$TARGET
OBJECTS_DIR = $$BUILD_DATA_DIR/obj
MOC_DIR = $$BUILD_DATA_DIR/moc
RCC_DIR = $$BUILD_DATA_DIR/qrc
UI_DIR = $$BUILD_DATA_DIR/ui

# C++ flags
QMAKE_CXXFLAGS_WARN_ON += -Wall -Werror
QMAKE_CXXFLAGS += -pthread -pedantic-errors

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
    ../src/Game.cpp \
    ../src/Tetromino.cpp



