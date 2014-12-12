# Moblok'
Moblok' is just another tetris clone, as simple as that!.

## Playing the latest release

1. Go to the [releases page](https://github.com/Neodivert/moblok/releases).
2. Find and download the latest release that matches your OS and architecture.
3. (Windows only): Unzip the downloaded file and execute moblok.exe.
3. (Linux only - DEB): Unzip and install the downloaded DEB package. Then, open a terminal and execute "moblok".
4. Enjoy!.

## Building Moblok' from code

### Dependencies

Building tools:
- [g++ (C++ compiler)](http://gcc.gnu.org/).
- [Qt Creator](http://qt-project.org/wiki/category:tools::qtcreator)
- [cmake 2.8](http://www.cmake.org/)

Libraries (both development and runtime versions):
- [SDL 2](http://www.libsdl.org/)
- [SDL_image 2](http://www.libsdl.org/projects/SDL_image/)
- [SDL_mixer 2](http://www.libsdl.org/projects/SDL_mixer/)
- [SDL_ttf 2](http://www.libsdl.org/projects/SDL_ttf/)

### Donwloading and building

1. Install the dependencies.

 ```
 sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev fonts-liberation
 ```

2. Clone the [Moblok' repository at Github](https://github.com/Neodivert/moblok/)

 ```
 git clone git@github.com:moisesjbc/moblok.git
 ```

3. Enter in Moblok' directory

 ```
 cd moblok
 ```

4. Build the game

 ```
 cmake .
 make
 sudo make install
 ```

5. Enjoy!

## License

### Own work

The source code of the game (directory "source") is under the GPLv3 license. You can find a copy of this license in the file share/moblok/license/LICENSE.moblok.txt.

The images used by the game (directory "share/moblok/img/") are licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
