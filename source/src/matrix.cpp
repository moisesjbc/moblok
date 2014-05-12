
/*                                             Includes                                        */
/***********************************************************************************************/

#include <matrix.hpp>



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

    NewTetromino( (rand()%7)+1 );
}


/***********************************************************************************************/
/*                                   3. Current tetromino manamegement                         */
/***********************************************************************************************/

int Matrix::NewTetromino( int color ) throw()
{
    tetromino_.color_ = color;
    tetromino_.x_ = TETROMINO_X0;
    tetromino_.y_ = TETROMINO_Y0;

    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[LAST_POS][i][X] = -1;
        tetromino_.blocks_[LAST_POS][i][Y] = -1;

        tetromino_.blocks_[CURRENT_POS][i][X] = tetromino_.x_ + Tetrominos[color-1][i][X];
        tetromino_.blocks_[CURRENT_POS][i][Y] = tetromino_.y_ + Tetrominos[color-1][i][Y];

        if( GetCell( tetromino_.blocks_[CURRENT_POS][i][X], tetromino_.blocks_[CURRENT_POS][i][Y] ) ) return -1;
    }
    return 0;
}

int Matrix::MoveTetromino( const int& dx ) throw()
{
    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[AUX][i][X] = tetromino_.blocks_[CURRENT_POS][i][X]+dx;
        if( GetCell( tetromino_.blocks_[AUX][i][X], tetromino_.blocks_[CURRENT_POS][i][Y] ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[LAST_POS][i][X] = tetromino_.blocks_[CURRENT_POS][i][X];
        tetromino_.blocks_[LAST_POS][i][Y] = tetromino_.blocks_[CURRENT_POS][i][Y];

        tetromino_.blocks_[CURRENT_POS][i][X] = tetromino_.blocks_[AUX][i][X];
        tetromino_.blocks_[CURRENT_POS][i][Y] = tetromino_.blocks_[LAST_POS][i][Y];
    }
    tetromino_.x_ += dx;

    return 0;
}

int Matrix::RotateTetromino() throw()
{
    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[AUX][i][X] = tetromino_.x_ - (tetromino_.blocks_[CURRENT_POS][i][Y]-tetromino_.y_) - 1;
        tetromino_.blocks_[AUX][i][Y] = tetromino_.y_ + (tetromino_.blocks_[CURRENT_POS][i][X]-tetromino_.x_);

        if( GetCell( tetromino_.blocks_[AUX][i][X], tetromino_.blocks_[AUX][i][Y] ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[LAST_POS][i][X] = tetromino_.blocks_[CURRENT_POS][i][X];
        tetromino_.blocks_[LAST_POS][i][Y] = tetromino_.blocks_[CURRENT_POS][i][Y];

        tetromino_.blocks_[CURRENT_POS][i][X] = tetromino_.blocks_[AUX][i][X];
        tetromino_.blocks_[CURRENT_POS][i][Y] = tetromino_.blocks_[AUX][i][Y];
    }

    return 0;
}

int Matrix::TetrominoFall( const int& dy ) throw()
{
    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[AUX][i][Y] = tetromino_.blocks_[CURRENT_POS][i][Y] + dy;
        if( GetCell( tetromino_.blocks_[CURRENT_POS][i][X], tetromino_.blocks_[AUX][i][Y] )  )
        {
            FixTetromino();
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        tetromino_.blocks_[LAST_POS][i][X] = tetromino_.blocks_[CURRENT_POS][i][X];
        tetromino_.blocks_[LAST_POS][i][Y] = tetromino_.blocks_[CURRENT_POS][i][Y];

        tetromino_.blocks_[CURRENT_POS][i][X] = tetromino_.blocks_[LAST_POS][i][X];
        tetromino_.blocks_[CURRENT_POS][i][Y] = tetromino_.blocks_[AUX][i][Y];
    }
    tetromino_.y_ += dy;

    return 0;
}

void Matrix::FixTetromino() throw()
{
    for( int j=0; j<4; j++ ){
        SetCell( tetromino_.blocks_[CURRENT_POS][j][X], tetromino_.blocks_[CURRENT_POS][j][Y], tetromino_.color_ );
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

int Matrix::EraseLines() throw()
{
    int res = 0;
    int i, min=255, max=0;

    for( i=0; i<4; i++ ){
        if( tetromino_.blocks_[CURRENT_POS][i][Y] < min ){
            min = tetromino_.blocks_[CURRENT_POS][i][Y];
        }
        if( tetromino_.blocks_[CURRENT_POS][i][Y] > max ){
            max = tetromino_.blocks_[CURRENT_POS][i][Y];
        }
    }

    for( i=max; i>=min; ){
        if( EraseLine( i ) == 0 ){
            res++;
            min++;
        }else{
            i--;
        }
    }

    return res;
}


/***********************************************************************************************/
/*                                      3. Graphic functions.                                  */
/***********************************************************************************************/

int Matrix::Draw( SDL_Surface *screen, SDL_Surface *tileset ) throw()
{
    SDL_Rect srcRect_ = {0, 0, TILE_SIZE, TILE_SIZE};
    SDL_Rect dstRect_ = {MATRIX_X, MATRIX_Y, 0, 0};
    for( unsigned int i=2; i<(MATRIX_H+2); i++ ){
        for( unsigned int j=0; j<MATRIX_W; j++ ){
            srcRect_.x = cells_[i][j] << TILE_SIZE_2;
            if( SDL_BlitSurface( tileset, &srcRect_, screen, &dstRect_ ) < 0 ){
                return -1;
            }
            dstRect_.x += TILE_SIZE;
        }
        dstRect_.x = MATRIX_X;
        dstRect_.y += TILE_SIZE;
    }

    return 0;
}

int Matrix::DrawTetromino( SDL_Surface *surface, SDL_Surface *tileset ) throw()
{
    SDL_Rect srcRect = { (Sint16)(tetromino_.color_<<TILE_SIZE_2), 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };
    SDL_Rect dstRect = { 0, 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };

    // Deletes the last position.
    for( int i=0; i<4; i++ ){
        if( tetromino_.blocks_[LAST_POS][i][Y] >= 2 ){
            dstRect.x = MATRIX_X+((tetromino_.blocks_[LAST_POS][i][X])<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((tetromino_.blocks_[LAST_POS][i][Y]-2)<<TILE_SIZE_2);
            SDL_FillRect( surface, &dstRect, 0xFFFFFFFF );
        }
    }

    // Draws the new one.
    for( int i=0; i<4; i++ ){
        if( tetromino_.blocks_[CURRENT_POS][i][Y] >= 2 ){
            dstRect.x = MATRIX_X+(tetromino_.blocks_[CURRENT_POS][i][X]<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((tetromino_.blocks_[CURRENT_POS][i][Y]-2)<<TILE_SIZE_2);
            if( SDL_BlitSurface( tileset, &srcRect, surface, &dstRect ) < 0 ) return -1;
        }
    }

    return 0;
}
