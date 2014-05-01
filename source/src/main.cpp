
#include <Tetris.hpp>
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
            std::cout << Mix_GetError() << std::endl;
            exit(1);
        }

        atexit( SDL_Quit );
        atexit( Mix_CloseAudio );

        Tetris tetris;

        tetris.Start();

    }catch( const char errorMsg[] ){
        std::cout << errorMsg << std::endl;
    }

	return 0;
}
