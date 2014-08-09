
/*                                             Includes                                        */
/***********************************************************************************************/

#include <matrix.hpp>
#include <iostream>



/*                                        Global constants                                     */
/***********************************************************************************************/

char errorMsg[151] = "\0";

/*                                         Type definitions                                    */
/***********************************************************************************************/


/***********************************************************************************************/
/*                               1. Initialization and destruction.                            */
/***********************************************************************************************/

Matrix::Matrix()
{
    Reset();
}


/***********************************************************************************************/
/*                                       2. Cells management.                                  */
/***********************************************************************************************/

void Matrix::SetCell( CUint& x, CUint& y, CUint& cell ) throw()
{
    if( ( x < MATRIX_W ) && ( y < (MATRIX_H+2) ) && ( cell < N_COLORS ) ){
        cells_[y][x] = cell;
    }
}

int Matrix::GetCell( CUint& x, CUint& y ) const throw()
{
    if( ( x < MATRIX_W ) && ( y < (MATRIX_H+2) ) ){
        return cells_[y][x];
    }else{
        return -1;
    }
}

void Matrix::Reset() throw()
{
    for( unsigned int i=0; i<(MATRIX_H+2); i++ ){
        for( unsigned int j=0; j<MATRIX_W; j++ ){
            cells_[i][j] = 0;
        }
    }
}


/***********************************************************************************************/
/*                                         4. Matrix update                                    */
/***********************************************************************************************/

int Matrix::EraseLine( const int& line ) throw()
{
    unsigned int i, j, k;

    for( i=0; i<MATRIX_W; i++ ){
        if( !cells_[line][i] ){
            return -1;
        }
    }

    for( j=line; j>0; j-- ){
        for( k=0; k<MATRIX_W; k++ ){
            cells_[j][k] = cells_[j-1][k];
        }
    }

    for( k=0; k<MATRIX_W; k++ ){
        cells_[0][k] = 0;
    }

    return 0;
}



int Matrix::EraseLines( int lowestRow, int highestRow ) throw()
{
    int res = 0;
    int currentRow;

    for( currentRow = highestRow; currentRow >= lowestRow; ){
        if( EraseLine( currentRow ) == 0 ){
            res++;
            //lowestRow++;
        }else{
            currentRow--;
        }
    }
    return res;
}



/***********************************************************************************************/
/*                                      3. Graphic functions.                                  */
/***********************************************************************************************/

int Matrix::Draw( SDL_Renderer* renderer, SDL_Texture* tileset ) throw()
{
    unsigned int row, column;

    SDL_Rect srcRect_ = {0, 0, TILE_SIZE, TILE_SIZE};
    SDL_Rect dstRect_ = {MATRIX_X, MATRIX_Y, TILE_SIZE, TILE_SIZE};
    for( row = 2; row < (MATRIX_H+2); row++ ){
        for( column=0; column<MATRIX_W; column++ ){
            srcRect_.x = cells_[row][column] << TILE_SIZE_2;
            SDL_RenderCopy( renderer, tileset, &srcRect_, &dstRect_ );
            dstRect_.x += TILE_SIZE;
        }
        dstRect_.x = MATRIX_X;
        dstRect_.y += TILE_SIZE;
    }

    return 0;
}

/*
int Matrix::DrawTetromino( SDL_Renderer* renderer, SDL_Texture* tileset ) throw()
{
    SDL_Rect srcRect = { (Sint16)(tetromino_.color_<<TILE_SIZE_2), 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };
    SDL_Rect dstRect = { 0, 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };

    // Deletes the last position.
    for( int i=0; i<4; i++ ){
        if( tetromino_.blocks_[LAST_POS][i][Y] >= 2 ){
            dstRect.x = MATRIX_X+((tetromino_.blocks_[LAST_POS][i][X])<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((tetromino_.blocks_[LAST_POS][i][Y]-2)<<TILE_SIZE_2);
            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
            SDL_RenderFillRect( renderer, &dstRect );
        }
    }

    // Draws the new one.
    for( int i=0; i<4; i++ ){
        if( tetromino_.blocks_[CURRENT_POS][i][Y] >= 2 ){
            dstRect.x = MATRIX_X+(tetromino_.blocks_[CURRENT_POS][i][X]<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((tetromino_.blocks_[CURRENT_POS][i][Y]-2)<<TILE_SIZE_2);
            if( SDL_RenderCopy( renderer, tileset, &srcRect, &dstRect ) < 0 ) return -1;
        }
    }

    return 0;
}
*/
