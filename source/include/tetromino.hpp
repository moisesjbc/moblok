/*
    Module      : Tetromino
    Author      : Moisés J. Bonilla Caraballo
    Description : This file contents all the extern libraries inclusions, the tetromino's shapes
    (Defined as a 3 dimentional array) and struct "Tetromino" used to manage the current tetromino
    in game.
*/

#ifndef TETROMINO_HPP
#define TETROMINO_HPP

/*                                             Includes                                        */
/***********************************************************************************************/


#include <stdexcept>
#include <matrix.hpp>
#include <resource_loader.hpp>


/*                                    Global variables and constants                           */
/***********************************************************************************************/

const int Tetrominos[][4][2] =
{
    { { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 } },
    { { -1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } },
    { { -2, 0 }, { -1, 0 }, { 0, 0 }, { 0, -1 }  },
    { { -1, -1 }, { -1, 0 }, { 0, -1 }, { 0, 0 } },

    { { -1, 0 }, { 0, 0 }, { 0, -1 }, { 1, -1 } },
    { { -2, 0 }, { -1, 0 }, { -1, -1 }, { 0, 0 } },
    { { -1, -1 }, { 0, -1 }, { 0, 0 }, { 1, 0 } }
};

const int LAST_POS = 0;
const int CURRENT_POS = 1;
const int AUX = 2;

const int TETROMINO_X0 = 5;
const int TETROMINO_Y0 = 1;


/*                                        Type declarations                                    */
/***********************************************************************************************/

class Tetromino {
    private:
        SDL_Texture* texture_;
        Matrix& gameMatrix_;

        int blocks_[4][2];
        int x_, y_;
        int color_;


    public:
        /***
         * 1. Construction
         ***/
        Tetromino( const ResourceLoader* resourceLoader, SDL_Renderer* renderer, Matrix& gameMatrix );


        /***
         * 2. Initialization
         ***/
        int Reset( int color );


        /***
         * 3. Updating
         ***/
        int MoveTetromino( const int& dx );
        int RotateTetromino();
        int TetrominoFall( const int& dy = 1 );
        void FixTetromino();


        /***
         * 4. Drawing
         ***/
        int Draw( SDL_Renderer* renderer );
};

#endif
// TETROMINO_HPP
