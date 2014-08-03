
#include <tetris.hpp>
#include <iostream>
using namespace std;

int main( int argc, char** argv )
{
    (void)argc;
    (void)argv;

    try{
        if( SDL_Init( SDL_INIT_VIDEO ) ){
            std::cerr << SDL_GetError() << std::endl;
            exit(1);
        }
        if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0 ){
            std::cerr << Mix_GetError() << std::endl;
            exit(1);
        }
        if( TTF_Init() == -1 ){
            std::cerr << TTF_GetError() << std::endl;
            exit(2);
        }

        atexit( SDL_Quit );
        atexit( Mix_Quit );
        atexit( TTF_Quit );

        Tetris tetris;

        tetris.start();

    }catch( const char errorMsg[] ){
        std::cerr << errorMsg << std::endl;
    }

	return 0;
}
