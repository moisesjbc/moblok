/*
    Module      : Matrix
    Author      : Moisés J. Bonilla Caraballo
    Description : Class which manages the matrix and current tetromino in game.
*/


/*                                             Includes                                        */
/***********************************************************************************************/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <tetromino.hpp>

extern "C" {
    #include <SDL2/SDL.h>
}

typedef const unsigned int CUint;

/*                                        Global constants                                     */
/***********************************************************************************************/

const unsigned int MATRIX_X = 352;
const unsigned int MATRIX_Y = 64;
const unsigned int MATRIX_W = 10;
const unsigned int MATRIX_H = 20;


const unsigned int N_COLORS = 8;
const unsigned int TILE_SIZE = 32;
const unsigned int TILE_SIZE_2 = 5;
const unsigned int X = 0;
const unsigned int Y = 1;
const int RES_X = 1024;
const int RES_Y = 768;

extern char errorMsg[151];

/*                                        Type declarations                                    */
/***********************************************************************************************/

/*
    NOTE : All the methods  of this class that returns a value except "int EraseLines()"
    returns 0 if they succeded. Otherwise they return -1.
*/

class Matrix {
    private:
        int cells_[MATRIX_H+2][MATRIX_W];
        Tetromino tetromino_;

    public:
        /***************************************************************************************/
        /*                                1. Initialization.                                   */
        /***************************************************************************************/
        Matrix();

        /***************************************************************************************/
        /*                               2. Cells management.                                  */
        /***************************************************************************************/
        void SetCell( CUint& x, CUint& y, CUint& cell ) throw();
        int GetCell( CUint& x, CUint& y )               const throw();
        void Reset()                                    throw();
            // Sets all the cells to zero (Empty) and creates a new random tetromino.

        /***************************************************************************************/
        /*                         3. Current tetromino manamegement.                          */
        /***************************************************************************************/
        int NewTetromino( int color )           throw();
            // It creates a new tetromino with "color" color (Color also determines
            // tetromino's shape).
        int MoveTetromino( const int& dx )      throw();
            // It moves the current tetromino "dx" cells horizontally.
        int RotateTetromino()                   throw();
            // It rotates the current tetromino to the left.
        int TetrominoFall( const int& dy = 1 )  throw();
            // Current tetromino falls "dy" positions.
        void FixTetromino()                     throw();

        /***************************************************************************************/
        /*                                5. Matrix update.                                    */
        /***************************************************************************************/
        int EraseLine( const int &line )    throw();
        int EraseLines()                    throw();

        /***************************************************************************************/
        /*                              6. Graphic functions.                                  */
        /***************************************************************************************/
        int Draw( SDL_Renderer* renderer, SDL_Texture* tileset )            throw();
        int DrawTetromino( SDL_Renderer* renderer, SDL_Texture* tileset )   throw();
};


#endif
// MATRIX_HPP
