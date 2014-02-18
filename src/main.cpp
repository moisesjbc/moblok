
#include<iostream>

#include"Tetris.hpp"

int main( int argc, char** argv )
{
    SDL_Surface *screen;

    try{
        if( SDL_Init( SDL_INIT_VIDEO ) ){
            std::cerr << SDL_GetError() << std::endl;
            exit(1);
        }
        atexit( SDL_Quit );

        screen = SDL_SetVideoMode( 1024, 768, 8, SDL_ANYFORMAT );

        SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 20, 171, 180 ) );


        Tetris tetris( screen, 300, 50, 10, 20 );

        if( !screen ){
            if( SDL_Init( SDL_INIT_VIDEO ) ){
                std::cout << SDL_GetError() << std::endl;
                exit(1);
            }
        }

        std::cout << tetris.Draw() << std::endl;

        SDL_Flip( screen );

        tetris.GameLoop();

    }catch( std::runtime_error& e ){
        std::cout << e.what() << std::endl;
    }
}
