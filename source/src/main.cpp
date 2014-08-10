
#include <tetris.hpp>
#include <iostream>
#include <exception>
using namespace std;

int main( int argc, char** argv )
{
    (void)argc;
    (void)argv;

    try{
        Tetris tetris;
        tetris.run();
    }catch( std::exception& ex ){
        std::cerr << ex.what() << std::endl;
        return 1;
    }

	return 0;
}
