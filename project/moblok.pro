TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL -lSDL_image

HEADERS += \
    ../src/Matrix.hpp \
    ../src/Player.hpp \
    ../src/Tetris.hpp \
    ../src/Tetromino.hpp

SOURCES += \
    ../src/main.cpp \
    ../src/Matrix.cpp \
    ../src/Player.cpp \
    ../src/Tetris.cpp \
    ../src/Tetromino.cpp
