
#include <tetromino.hpp>
#include <iostream>

/***
 * 1. Construction
 ***/

Tetromino::Tetromino( const ResourceLoader* resourceLoader, SDL_Renderer* renderer, Matrix& gameMatrix ) :
    gameMatrix_( gameMatrix )
{
    texture_ = resourceLoader->loadImage( "tileset.png", renderer );

    Reset( (rand()%7)+1 );
}


/***
 * 2. Initialization
 ***/

int Tetromino::Reset( int color ) throw()
{
    color_ = color;
    x_ = TETROMINO_X0;
    y_ = TETROMINO_Y0;

    for( int i=0; i<4; i++ ){
        blocks_[i][X] = x_ + Tetrominos[color-1][i][X];
        blocks_[i][Y] = y_ + Tetrominos[color-1][i][Y];

        if( gameMatrix_.GetCell( blocks_[i][X], blocks_[i][Y] ) ) return -1;
    }

    return 0;
}


/***
 * 3. Updating
 ***/

int Tetromino::MoveTetromino( const int& dx ) throw()
{
    for( int i=0; i<4; i++ ){
        if( gameMatrix_.GetCell( blocks_[i][X] + dx, blocks_[i][Y] ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i][X] += dx;
    }
    x_ += dx;

    return 0;
}


int Tetromino::RotateTetromino() throw()
{
    for( int i=0; i<4; i++ ){
        int aux_x = blocks_[i][X];

        if( gameMatrix_.GetCell( x_ - (blocks_[i][Y]-y_) - 1, y_ + (aux_x-x_) ) ){
                return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        int aux_x = blocks_[i][X];
        blocks_[i][X] = x_ - (blocks_[i][Y]-y_) - 1;
        blocks_[i][Y] = y_ + (aux_x-x_);
    }

    return 0;
}

int Tetromino::TetrominoFall( const int& dy ) throw()
{
    for( int i=0; i<4; i++ ){
        if( gameMatrix_.GetCell( blocks_[i][X], blocks_[i][Y] + dy )  )
        {
            FixTetromino();
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i][Y] += dy;
    }
    y_ += dy;

    return 0;
}

void Tetromino::FixTetromino() throw()
{
    gameMatrix_.Print();

    std::cout << "Fixing tetromino!" << std::endl;
    for( int j=0; j<4; j++ ){
        gameMatrix_.SetCell( blocks_[j][X], blocks_[j][Y], color_ );
    }

    gameMatrix_.Print();
}


/***
 * 4. Drawing
 ***/

int Tetromino::Draw( SDL_Renderer* renderer )
{
    SDL_Rect srcRect = { (Sint16)(color_<<TILE_SIZE_2), 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };
    SDL_Rect dstRect = { 0, 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };

    for( int i=0; i<4; i++ ){
        if( blocks_[i][Y] >= 2 ){
            dstRect.x = MATRIX_X+(blocks_[i][X]<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((blocks_[i][Y]-2)<<TILE_SIZE_2);
            if( SDL_RenderCopy( renderer, texture_, &srcRect, &dstRect ) < 0 ) return -1;
        }
    }

    return 0;
}
