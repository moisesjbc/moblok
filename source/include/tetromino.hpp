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

const int TETROMINO_X0 = 5 * TILE_SIZE;
const int TETROMINO_Y0 = 1 * TILE_SIZE;


/*                                        Type declarations                                    */
/***********************************************************************************************/

class Tetromino {
    public:
        /***
         * 1. Construction
         ***/
        Tetromino( const ResourceLoader* resourceLoader, SDL_Renderer* renderer, Matrix& gameMatrix );


        /***
         * 2. Initialization
         ***/
        int reset( int color );


        /***
         * 3. Updating
         ***/
        int moveHorizontally( const int& cells );
        int rotate();
        int fall( const int& dy = 10 ); // TODO: Remove the argument and rename as update()?


        /***
         * 4. Drawing
         ***/
        int draw( SDL_Renderer* renderer );


        /***
         * 5. Tetromino fixing.
         ***/
    private:
        void fixToGameMatrix();


    private:
        SDL_Texture* texture_;
        Matrix& gameMatrix_;

        PixelPos pos_;
        PixelPos blocks_[4];
        int color_;

        PixelPos pivotPoint_;
};

#endif
// TETROMINO_HPP
