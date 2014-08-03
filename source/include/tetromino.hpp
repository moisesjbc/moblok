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
    public:
        int blocks_[3][4][2];
        int x_, y_;
        int color_;
};

#endif
// TETROMINO_HPP
