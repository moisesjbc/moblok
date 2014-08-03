
#include <resource_loader.hpp>

/***
 * 1. Construction
 ***/

ResourceLoader::ResourceLoader( std::vector< std::string > dataDirectories ) :
    dataDirectories_( dataDirectories )
{}


/***
 * 2. Loading methods
 ***/

// FIXME: Duplicated code.
SDL_Texture* ResourceLoader::loadImage( const std::string relativePath, SDL_Renderer* renderer ) const
{
    unsigned int i = 0;
    std::string fullImagePath;
    SDL_Surface* imageSurface = nullptr;
    SDL_Texture* image = nullptr;

    while( !image && (i < dataDirectories_.size() ) ){
        fullImagePath = dataDirectories_[i] + "/img/" + relativePath;

        imageSurface = IMG_Load( fullImagePath.c_str() );

        i++;
    }

    if( !imageSurface ){
        throw std::runtime_error( IMG_GetError() );
    }

    image = SDL_CreateTextureFromSurface( renderer, imageSurface );

    return image;
}


// FIXME: Duplicated code.
Mix_Music* ResourceLoader::loadMusic( const std::string relativePath ) const
{
    unsigned int i = 0;
    std::string fullMusicPath;
    Mix_Music* music = nullptr;

    while( !music && (i < dataDirectories_.size() ) ){
        fullMusicPath = dataDirectories_[i] + "/music/" + relativePath;

        music = Mix_LoadMUS( fullMusicPath.c_str() );

        i++;
    }

    if( !music ){
        throw std::runtime_error( IMG_GetError() );
    }

    return music;
}


TTF_Font *ResourceLoader::loadFont( const std::string relativePath, int ptSize ) const
{
    unsigned int i = 0;
    std::string fullFontPath;
    TTF_Font* font = nullptr;

    while( !font && (i < dataDirectories_.size() ) ){
        fullFontPath = dataDirectories_[i] + "/fonts/" + relativePath;

        font = TTF_OpenFont( fullFontPath.c_str(), ptSize );

        i++;
    }

    if( !font ){
        throw std::runtime_error( TTF_GetError() );
    }

    return font;
}
