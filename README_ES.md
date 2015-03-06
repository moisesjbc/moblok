# Moblok'

[View in English](README.md)

![Captura de pantalla de Moblok'](img/moblok.png "Captura de pantalla de Moblok'")

## Descripción

Moblok' es un clon del juego Tetris. Ha sido desarrollado usando C++ y las librerías SDL (2.0).

## Current status

**Inactivo**. Se puede descargar una demo jugable desde la [página de versiones publicadas](https://github.com/moisesjbc/moblok/releases).

## Jugando a la última versión publicada

1. Ve a la [página de versiones publicadas](https://github.com/Neodivert/moblok/releases).
2. Encuentra y descarga la última versión para tu sistema operativo y arquitectura.
3. (Windows): Descomprime el fichero descargado y ejecuta moblok.exe.
3. (GNU/Linux - DEB): Descomprime e instala el paquete DEB descargado. A continuación, ejecuta Moblok' desde el gestor de aplicaciones de Ubuntu.
4. ¡Disfruta!.

## Construyendo Moblok' desde código (Probado en Ubuntu 14.04)

### Dependencias

Herramientas de construcción:
- [g++ (Compilador de C++)](http://gcc.gnu.org/).
- [cmake 2.8](http://www.cmake.org/)

Librerías (ambas versiones: desarrollo y de ejecución):
- [SDL 2](http://www.libsdl.org/)
- [SDL_image 2](http://www.libsdl.org/projects/SDL_image/)
- [SDL_mixer 2](http://www.libsdl.org/projects/SDL_mixer/)
- [SDL_ttf 2](http://www.libsdl.org/projects/SDL_ttf/)

### Descargando y construyendo

1. Instala las dependencias.

 ```
 sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev fonts-liberation
 ```

2. Clona el [repositorio de Moblok' en Github](https://github.com/Neodivert/moblok/)

 ```
 git clone git@github.com:moisesjbc/moblok.git
 ```

3. Entra en el directorio de Moblok'

 ```
 cd moblok
 ```

4. Construye el juego

 ```
 cmake .
 make
 sudo make install
 ```

5. Ejecuta el juego, ¡y disfruta!

 ```
 moblok
 ```

## Licencia

### Trabajo propio

* **Código fuente:** GPLv3.
* **Imágenes:** [Creative Commons Attribution 4.0 International (CC BY 4.0)](http://creativecommons.org/licenses/by/4.0/).

## Trabajo de terceros

* **Librerías SDL, SDL_image, SDL_mixer and SDL_ttf:** La licencia de cada una puede encontrarse en sus respectivos sitios web.
* **Music:** La música usada en el juego se ha descargado desde Wikimedia Commons en [este enlace](http://commons.wikimedia.org/wiki/File:Tetris_theme.ogg?uselang=es). Tal como se menciona en dicho enlace, la música ha sido creada por el usuario "Bogozi" y licenciada bajo una licencia [Creative Commons Attribution-ShareAlike 3.0 Unported license (CC BY-SA 3.0)](http://creativecommons.org/licenses/by-sa/3.0/).
* **Fuente:** La fuente usada en Moblok' es LiberationSans-Bold.ttf, [licensiada bajo SIL Open Font License (version 2 en adelante) o GPL v2 con algunas excepciones (versiones anteriores)](http://en.wikipedia.org/wiki/Liberation_fonts).

