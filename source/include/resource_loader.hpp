
#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP

#include <config.hpp>
#include <vector>
#include <string>
#include <stdexcept>

extern "C" {
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_video.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_ttf.h>
}

class ResourceLoader
{
    private:
        const std::vector< std::string > dataDirectories_;

    public:
        /***
         * 1. Construction
         ***/
        ResourceLoader( std::vector< std::string > dataDirectories );

        /***
         * 2. Loading methods
         ***/
        SDL_Texture* loadImage( const std::string relativePath, SDL_Renderer* renderer ) const;
        Mix_Music* loadMusic( const std::string relativePath ) const;
        TTF_Font* loadFont( const std::string relativePath, int ptSize ) const;
};


#endif
// RESOURCE_LOADER_HPP
