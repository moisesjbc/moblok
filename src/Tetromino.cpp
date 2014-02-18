
/*                                             Includes                                        */
/***********************************************************************************************/

#include"Tetromino.hpp"

/*                                        Global constants                                     */
/***********************************************************************************************/

int Tetrominos[][4][2] =
{
    { { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 } }, // OK.
    { { -1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } }, // OK.
    { { -2, 0 }, { -1, 0 }, { 0, 0 }, { 0, -1 }  }, // OK.
    { { -1, -1 }, { -1, 0 }, { 0, -1 }, { 0, 0 } }, // OK.

    { { -1, 0 }, { 0, 0 }, { 0, -1 }, { 1, -1 } }, // OK.
    { { -2, 0 }, { -1, 0 }, { -1, -1 }, { 0, 0 } }, // OK
    { { -1, -1 }, { 0, -1 }, { 0, 0 }, { 1, 0 } } // OK.
};

const int LAST_POS = 0;
const int CURRENT_POS = 1;
const int AUX = 2;

/*                                       Type decfinitions                                     */
/***********************************************************************************************/


/*                                       1. Initialization                                     */

Tetromino::Tetromino( Matrix &matrix, const int& x, const int& y ) : x0_(x), y0_(y), matrix_(&matrix)
{
    New();
}

int Tetromino::New()
{
    srand( SDL_GetTicks() );
    int aux = (rand()%7);
    color_ = aux+1;
    x_ = x0_;
    y_ = y0_;

    for( int i=0; i<4; i++ ){
        blocks_[LAST_POS][i][X] = -1;
        blocks_[LAST_POS][i][Y] = -1;

        blocks_[CURRENT_POS][i][X] = x_ + Tetrominos[aux][i][X];
        blocks_[CURRENT_POS][i][Y] = y_ + Tetrominos[aux][i][Y];
        if( matrix_->GetCell( blocks_[CURRENT_POS][i][X], blocks_[CURRENT_POS][i][Y] ) ) return 0;
    }
    return 1;
}


/*                                      2. Tetromino movement.                                 */

int Tetromino::Move( const int& dx )
{
    for( int i=0; i<4; i++ ){
        blocks_[AUX][i][X] = blocks_[CURRENT_POS][i][X]+dx;
        if( matrix_->GetCell( blocks_[AUX][i][X], blocks_[CURRENT_POS][i][Y] ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[LAST_POS][i][X] = blocks_[CURRENT_POS][i][X];
        blocks_[LAST_POS][i][Y] = blocks_[CURRENT_POS][i][Y];

        blocks_[CURRENT_POS][i][X] = blocks_[AUX][i][X];
        blocks_[CURRENT_POS][i][Y] = blocks_[LAST_POS][i][Y];
    }
    x_ += dx;

    return 0;
}


int Tetromino::Rotate(){

    for( int i=0; i<4; i++ ){
        blocks_[AUX][i][X] = x_ - (blocks_[CURRENT_POS][i][Y]-y_) - 1;
        blocks_[AUX][i][Y] = y_ + (blocks_[CURRENT_POS][i][X]-x_);

        if( matrix_->GetCell( blocks_[AUX][i][X], blocks_[AUX][i][Y] ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[LAST_POS][i][X] = blocks_[CURRENT_POS][i][X];
        blocks_[LAST_POS][i][Y] = blocks_[CURRENT_POS][i][Y];

        blocks_[CURRENT_POS][i][X] = blocks_[AUX][i][X];
        blocks_[CURRENT_POS][i][Y] = blocks_[AUX][i][Y];
    }

    return 0;
}


int Tetromino::Fall( const int& dy)
{
    for( int i=0; i<4; i++ ){
        blocks_[AUX][i][Y] = blocks_[CURRENT_POS][i][Y] + dy;
        if( matrix_->GetCell( blocks_[CURRENT_POS][i][X], blocks_[AUX][i][Y] )  )
        {
            Fix();
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[LAST_POS][i][X] = blocks_[CURRENT_POS][i][X];
        blocks_[LAST_POS][i][Y] = blocks_[CURRENT_POS][i][Y];

        blocks_[CURRENT_POS][i][X] = blocks_[LAST_POS][i][X];
        blocks_[CURRENT_POS][i][Y] = blocks_[AUX][i][Y];
    }
    y_ += dy;

    return 0;
}


/*                                            3. Miscellaneous                                 */

void Tetromino::Fix()
{
    for( int j=0; j<4; j++ ){
        matrix_->SetCell( blocks_[CURRENT_POS][j][X], blocks_[CURRENT_POS][j][Y], color_ );
    }
}

void Tetromino::GetRange( int& minY, int& maxY ){
    minY = matrix_->GetH()+1;
    maxY = -1;
    for( int i=0; i<4; i++ ){
        if( blocks_[CURRENT_POS][i][Y] < minY ){
            minY = blocks_[CURRENT_POS][i][Y];
        }
        if( blocks_[CURRENT_POS][i][Y] > maxY ){
            maxY = blocks_[CURRENT_POS][i][Y];
        }
    }
}


/*                                       4. Graphic functios.                                  */

void Tetromino::Draw( SDL_Surface *surface, SDL_Surface *tileset )
{
    SDL_Rect srcRect = { (Uint16)(color_<<TILE_SIZE_2), 0, (Uint16)TILE_SIZE, (Uint16)TILE_SIZE };
    SDL_Rect dstRect = { 0, 0, (Uint16)TILE_SIZE, (Uint16)TILE_SIZE };

    // Deletes the last position.
    for( int i=0; i<4; i++ ){
        if( blocks_[LAST_POS][i][Y] >= 2 ){
            dstRect.x = matrix_->GetX()+((blocks_[LAST_POS][i][X])<<TILE_SIZE_2);
            dstRect.y = matrix_->GetY()+((blocks_[LAST_POS][i][Y]-2)<<TILE_SIZE_2);
            SDL_FillRect( surface, &dstRect, 0xFFFFFFFF );
        }
    }

    // Draws the new one.
    for( int i=0; i<4; i++ ){
        if( blocks_[CURRENT_POS][i][Y] >= 2 ){
            dstRect.x = matrix_->GetX()+(blocks_[CURRENT_POS][i][X]<<TILE_SIZE_2);
            dstRect.y = matrix_->GetY()+((blocks_[CURRENT_POS][i][Y]-2)<<TILE_SIZE_2);
            SDL_BlitSurface( tileset, &srcRect, surface, &dstRect );
        }
    }
}
