/*
    Module      :
    Author      :
    Description :
*/


/*                                             Includes                                        */
/***********************************************************************************************/

#include"Matrix.hpp"

#ifndef TETROMINO_HPP
#define TETROMINO_HPP


/*                                        Type declarations                                    */
/***********************************************************************************************/

class Tetromino {
    private:
        int blocks_[3][4][2];
        int x0_, y0_;
        int x_, y_;
        int color_;

        Matrix *matrix_;

    public:
        // 1. Initialization
        Tetromino( Matrix &matrix, const int& x, const int &y );
        int New();

        // 2. Tetromino movement.
        int Move( const int& dx );
        int Rotate();
        int Fall( const int &dy = 1 );

        // 3. Miscellaneous
        void Fix();
        void GetRange( int& minY, int& maxY );

        // 4. Graphic functios.
        void Draw( SDL_Surface *surface, SDL_Surface *tileset );
};

#endif
// TETROMINO_HPP
