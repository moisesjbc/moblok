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
#include <game_loop.hpp>

/*                                        Global constants                                     */
/***********************************************************************************************/



/*                                        Type declarations                                    */
/***********************************************************************************************/

class Tetris {
    public:
        /***
         * 1. Construction
         ***/
        Tetris();


        /***
         * 2. Destruction
         ***/
        ~Tetris();


        /***
         * 3. Execution
         ***/
        void run();


    private:
        /***
         * 4. Initialization
         ***/
        void initSDL();


    private:
        GameLoop *game_;
        SDL_Window* screen_; // TODO: Rename as window.
        Mix_Music *music_;
        SDL_Renderer* renderer_;

        ResourceLoader resourceLoader_;
};


#endif
// TETRIS_HPP
