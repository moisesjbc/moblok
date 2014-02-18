
/*                                             Includes                                        */
/***********************************************************************************************/

#include"Matrix.hpp"



/*                                        Global constants                                     */
/***********************************************************************************************/

const unsigned int MIN_W = 4;
const unsigned int MIN_H = 4;
const unsigned int MAX_W = 25;
const unsigned int MAX_H = 25;
const unsigned int N_COLORS = 8;
const unsigned int TILE_SIZE = 32;
const unsigned int TILE_SIZE_2 = 5;
const unsigned int X = 0;
const unsigned int Y = 1;

/*                                         Type definitions                                    */
/***********************************************************************************************/

/*                               1. Initialization and destruction.                            */

Matrix::Matrix( CUint& x, CUint& y, CUint& w, CUint& h )
    throw( std::runtime_error ): x_(x), y_(y), w_(w), h_(h)
{
    if( ( w_ >= MIN_W ) && ( h_ >=MIN_H ) && ( w_ <= MAX_W ) && ( h_ <= MAX_H ) ){
        // Allocate memory for the matrix.

        try {
            cells_ = new int* [h_+2];
            for( unsigned int i=0; i<h_+2; i++ ){
                cells_[i] = new int [w_];
                for( unsigned int j=0; j<w_; j++ ){
                    cells_[i][j] = 0;
                }
            }
        }catch( std::bad_alloc& ){
            throw std::runtime_error( "Matrix::Error - There isnt enough memory" );
        }

    }else{
        throw std::runtime_error( "Matrix::Error - Invalid matrix dimentions");
    }
}


Matrix::Matrix( CUint& w, CUint& h )
    throw( std::runtime_error ): x_(0), y_(0), w_(w), h_(h)
{
    if( ( w_ >= MIN_W ) && ( h_ >=MIN_H ) && ( w_ <= MAX_W ) && ( h_ <= MAX_H ) ){
        // Allocate memory for the matrix.
        try {
            cells_ = new int* [h_+2];
            for( unsigned int i=0; i<h_+2; i++ ){
                cells_[i] = new int [w_];
                for( unsigned int j=0; j<w_; j++ ){
                    cells_[i][j] = 0;
                }
            }
        }catch( std::bad_alloc& ){
            throw std::runtime_error( "Matrix::Error - There isnt enough memory" );
        }

    }else{
        throw std::runtime_error( "Matrix::Error - Invalid matrix dimentions");
    }
}


Matrix::~Matrix()
{
    for( unsigned int i=0; i<(h_+2); i++ ){
        delete [] cells_[i];
    }
    delete [] cells_;
}


/*                                       2. Cells management.                                  */

void Matrix::SetCell( CUint& x, CUint& y, CUint& cell )
{
    if( ( x < w_ ) && ( y < (h_+2) ) && ( cell < N_COLORS ) ){
        cells_[y][x] = cell;
    }
}

int Matrix::GetCell( CUint& x, CUint& y ){
    if( ( x < w_ ) && ( y < (h_+2) ) ){
        return cells_[y][x];
    }else{
        return -1;
    }
}

void Matrix::Clear(){
    for( unsigned int i=0; i<(h_+2); i++ ){
        for( unsigned int j=0; j<w_; j++ ){
            cells_[i][j] = 0;
        }
    }
}


/*                                         4. Matrix update                                    */

int Matrix::EraseLine( const int& line ){
    unsigned int i, j, k;

    for( i=0; i<w_; i++ ){
        if( !cells_[line][i] ){
            return 0;
        }
    }

    for( j=line; j>0; j-- ){
        for( k=0; k<w_; k++ ){
            cells_[j][k] = cells_[j-1][k];
        }
    }

    return 1;
}

int Matrix::EraseLines( unsigned int min, CUint& max )
{
    int res = 0;
    unsigned int i;

    if( ( min > max ) || ( min >= h_+2 ) || ( max >= h_+2 ) ) return 0;

    for( i=max; i>=min; ){
        if( EraseLine( i ) ){
            res = 1;
            min++;
        }else{
            i--;
        }
    }

    return res;
}


/*                                      3. Graphic functions.                                  */

int Matrix::Draw( SDL_Surface *screen, SDL_Surface *tileset )
{
    SDL_Rect srcRect_ = {0, 0, TILE_SIZE, TILE_SIZE};
    SDL_Rect dstRect_ = {x_, y_, 0, 0};
    for( unsigned int i=2; i<(h_+2); i++ ){
        for( unsigned int j=0; j<w_; j++ ){
            srcRect_.x = cells_[i][j] << TILE_SIZE_2;
            if( SDL_BlitSurface( tileset, &srcRect_, screen, &dstRect_ ) < 0 ){
                return -1;
            }
            dstRect_.x += TILE_SIZE;
        }
        dstRect_.x = x_;
        dstRect_.y += TILE_SIZE;
    }

    return 0;
}
