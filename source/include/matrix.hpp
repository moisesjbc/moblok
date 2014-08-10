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
    public:
        /***
         * 1. Construction
         ***/
        Matrix();


        /***
         * 2. Initialization
         ***/
        void reset();


        /***
         * 3. Cells management
         ***/
        int getCell( CUint& x, CUint& y ) const;
        void setCell( CUint& x, CUint& y, CUint& cell );


        /***
         * 4. Updating
         ***/
        int eraseCompletedRows( int firstRow = 0, int lastRow = N_MATRIX_ROWS - 1 );


        /***
         * 5. Drawing
         ***/
        int draw( SDL_Renderer* renderer, SDL_Texture* tileset );
        void print();


    private:
        /***
         * 6. Updating (private)
         ***/
        int eraseRowIfCompleted( const int &rowToBeChecked );

    private:
        int cells_[N_MATRIX_ROWS][N_MATRIX_COLUMNS];
};


#endif
// MATRIX_HPP
