/*
    Module      : Matrix
    Author      : Moisés J. Bonilla Caraballo
    Description : Class which manages the matrix and current tetromino in game.
*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

extern "C" {
    #include <SDL2/SDL.h>
}

typedef const unsigned int CUint;

const unsigned int MATRIX_X = 352;
const unsigned int MATRIX_Y = 64;

const unsigned int FIRST_VISIBLE_ROW = 1;
const unsigned int N_MATRIX_VISIBLE_ROWS = 20;
const unsigned int N_MATRIX_ROWS = N_MATRIX_VISIBLE_ROWS + FIRST_VISIBLE_ROW + 1;
const unsigned int N_MATRIX_COLUMNS = 10;

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

class Matrix {
    private:
        int cells_[N_MATRIX_ROWS][N_MATRIX_COLUMNS];

    public:
        /***
         * 1. Construction
         ***/
        Matrix();


        /***
         * 2. Initialization
         ***/
        void Reset();


        /***
         * 3. Cells management
         ***/
        int GetCell( CUint& x, CUint& y ) const;
        void SetCell( CUint& x, CUint& y, CUint& cell );


        /***
         * 4. Updating
         ***/
        int EraseLine( const int &line );
        int EraseLines( int firstRow = 0, int lastRow = N_MATRIX_ROWS - 1 );


        /***
         * 6. Drawing
         ***/
        int Draw( SDL_Renderer* renderer, SDL_Texture* tileset );
        void Print();
};


#endif
// MATRIX_HPP
