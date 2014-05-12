/*
    Module      : Tetris
    Author      : Moisés J. Bonilla Caraballo
    Description : Main game class. It takes the control once SDL was init at main().
*/

#ifndef TETRIS_HPP
#define TETRIS_HPP


/*                                             Includes                                        */
/***********************************************************************************************/

#include <resource_loader.hpp>
#include <game.hpp>

/*                                        Global constants                                     */
/***********************************************************************************************/



/*                                        Type declarations                                    */
/***********************************************************************************************/

class Tetris {
    private:
        Game *game_;
        SDL_Surface* screen_;
        Mix_Music *music_;

        ResourceLoader resourceLoader_;

    public:
        /***
         * 1. Construction and destruction
         ***/
        Tetris();
        ~Tetris();


        /***
         * 2. Game initialization
         ***/
        void start();
};


#endif
// TETRIS_HPP
