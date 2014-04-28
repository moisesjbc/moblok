# Moblok'
Moblok' is just another tetris clone, as simple as that!.

## Current project status
The project is currently inactive, and I don't plan to continue it any time soon. However, exist a downloable and playable demos for GNU/Linux and Windows (x86 and x86_64) so you can enjoy this masterpiece (sarcasm).

## Playing the latest demo

(*) The first three steps may not be necessary if this file is currently on your computer :-P.

1. Go to the [releases page](https://github.com/Neodivert/moblok/releases).
2. Find the latest release that matchs your OS and architecture.
3. Download and unzip it.
4. Execute moblok.exe and enjoy!.

## Building Moblok' from code

### Dependencies

Moblok' was developed using [QtCreator and qmake](http://qt-project.org/) so the direct way for you to build the game is to download these tools.

Moreover, you will also need the following libraries for building and running the game:
- [SDL 1.2](http://www.libsdl.org/)
- [SDL_image 1.2](http://www.libsdl.org/projects/SDL_image/release-1.2.html)
- [SDL_mixer 1.2](http://www.libsdl.org/projects/SDL_mixer/release-1.2.html)

### Donwloading and building

1. Install the dependencies listed in previous section.

2. Clone the [Moblok' repository at Github](https://github.com/Neodivert/moblok/)
```
git clone git@github.com:Neodivert/moblok 
```

3. Open the game's project file (project/moblok.pro) with QtCreator.

4. Build the game and enjoy it!.

## License

### Own work

The source code of the game (directory "src") is under the GPLv3 license. You can find a copy of this license in the file build/data/license/LICENSE.moblok.txt.

The images used by the game (directory "build/data/img/") are licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.

### Third-party work

The libraries SDL, SDL_image and SDL_mixer, as well as their dependencies are property of their respective owners. The licenses for every library used by the game is present in the directory "build/data/license/sdl*.

The music played in the game has been downloaded from Wikimedia Commons in the next url: http://commons.wikimedia.org/wiki/File:Tetris_theme.ogg?uselang=es. As stated by that url, the music has been made by Bogozi and it is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported license (CC BY-SA 3.0). To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/.

## Changelog

### v0.7.1
Added license advices and a README I forgot in previous release (Ooops!).

### v0.7.0
First demo. It allows you to play calmly to death (no score, no levels, no victory screen).
