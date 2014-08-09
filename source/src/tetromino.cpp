
#include <tetromino.hpp>

/***
 * 1. Construction
 ***/

Tetromino::Tetromino( const ResourceLoader* resourceLoader, SDL_Renderer* renderer, Matrix& gameMatrix ) :
    gameMatrix_( gameMatrix )
{
    texture_ = resourceLoader->loadImage( "tileset.png", renderer );
}


/***
 * 2. Initialization
 ***/

int Tetromino::NewTetromino( int color ) throw()
{
    color_ = color;
    x_ = TETROMINO_X0;
    y_ = TETROMINO_Y0;

    for( int i=0; i<4; i++ ){
        blocks_[LAST_POS][i][X] = -1;
        blocks_[LAST_POS][i][Y] = -1;

        blocks_[CURRENT_POS][i][X] = x_ + Tetrominos[color-1][i][X];
        blocks_[CURRENT_POS][i][Y] = y_ + Tetrominos[color-1][i][Y];

        if( gameMatrix_.GetCell( blocks_[CURRENT_POS][i][X], blocks_[CURRENT_POS][i][Y] ) ) return -1;
    }
    return 0;
}


/***
 * 3. Updating
 ***/

int Tetromino::MoveTetromino( const int& dx ) throw()
{
    for( int i=0; i<4; i++ ){
        blocks_[AUX][i][X] = blocks_[CURRENT_POS][i][X]+dx;
        if( gameMatrix_.GetCell( blocks_[AUX][i][X], blocks_[CURRENT_POS][i][Y] ) ){
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

int Tetromino::RotateTetromino() throw()
{
    for( int i=0; i<4; i++ ){
        blocks_[AUX][i][X] = x_ - (blocks_[CURRENT_POS][i][Y]-y_) - 1;
        blocks_[AUX][i][Y] = y_ + (blocks_[CURRENT_POS][i][X]-x_);

        if( gameMatrix_.GetCell( blocks_[AUX][i][X], blocks_[AUX][i][Y] ) ){
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

int Tetromino::TetrominoFall( const int& dy ) throw()
{
    for( int i=0; i<4; i++ ){
        blocks_[AUX][i][Y] = blocks_[CURRENT_POS][i][Y] + dy;
        if( gameMatrix_.GetCell( blocks_[CURRENT_POS][i][X], blocks_[AUX][i][Y] )  )
        {
            FixTetromino();
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

void Tetromino::FixTetromino() throw()
{
    for( int j=0; j<4; j++ ){
        gameMatrix_.SetCell( blocks_[CURRENT_POS][j][X], blocks_[CURRENT_POS][j][Y], color_ );
    }
}


/***
 * 4. Drawing
 ***/

int Tetromino::Draw( SDL_Renderer* renderer )
{
    SDL_Rect srcRect = { (Sint16)(color_<<TILE_SIZE_2), 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };
    SDL_Rect dstRect = { 0, 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };

    // Deletes the last position.
    /*
    for( int i=0; i<4; i++ ){
        if( blocks_[LAST_POS][i][Y] >= 2 ){
            dstRect.x = MATRIX_X+((blocks_[LAST_POS][i][X])<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((blocks_[LAST_POS][i][Y]-2)<<TILE_SIZE_2);
            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
            SDL_RenderFillRect( renderer, &dstRect );
        }
    }
    */

    // Draws the new one.
    for( int i=0; i<4; i++ ){
        if( blocks_[CURRENT_POS][i][Y] >= 2 ){
            dstRect.x = MATRIX_X+(blocks_[CURRENT_POS][i][X]<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((blocks_[CURRENT_POS][i][Y]-2)<<TILE_SIZE_2);
            if( SDL_RenderCopy( renderer, texture_, &srcRect, &dstRect ) < 0 ) return -1;
        }
    }

    return 0;
}
