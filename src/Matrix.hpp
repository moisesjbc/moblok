/*
    Module      :
    Author      :
    Description :
*/


/*                                             Includes                                        */
/***********************************************************************************************/


#ifdef __APPLE__
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
#else

#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <stdexcept>

#include <iostream>

#ifndef MATRIX_HPP
#define MATRIX_HPP

typedef const unsigned int CUint;

/*                                        Global constants                                     */
/***********************************************************************************************/

extern const unsigned int MAX_W; // = 25
extern const unsigned int MAX_H; // = 25
extern const unsigned int N_COLORS; // = 8
extern const unsigned int TILE_SIZE; // 32
extern const unsigned int TILE_SIZE_2; // 5
extern const unsigned int X;
extern const unsigned int Y;

/*                                        Type declarations                                    */
/***********************************************************************************************/

class Matrix {
    private:
        Sint16 x_, y_;
        unsigned int w_, h_;
        int **cells_;

    public:
        // 1. Initialization and destruction.
        Matrix( CUint& x, CUint& y, CUint& w, CUint& h ) throw( std::runtime_error );
        Matrix( CUint& w, CUint& h ) throw( std::runtime_error );

        ~Matrix();

        // 2. Cells management.
        void SetCell( CUint& x, CUint& y, CUint& cell );
        int GetCell( CUint& x, CUint& y );
        void Clear();

        // 3. Properties information
        int GetX(){ return x_; }
        int GetY(){ return y_; }
        int GetW(){ return w_; }
        int GetH(){ return h_+2; }

        // 4. Matrix update.
        int EraseLine( const int &line );
        int EraseLines( unsigned int min, CUint& max );

        // 5. Graphic functions.
        int Draw( SDL_Surface *screen, SDL_Surface *tileset );
};


#endif
// MATRIX_HPP
