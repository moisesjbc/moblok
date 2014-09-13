
#include <tetromino.hpp>

/***
 * 1. Construction
 ***/

Tetromino::Tetromino( const ResourceLoader* resourceLoader, SDL_Renderer* renderer, Matrix& gameMatrix ) :
    gameMatrix_( gameMatrix )
{
    texture_ = resourceLoader->loadImage( "tileset.png", renderer );

    reset( (rand()%7)+1 );
}


/***
 * 2. Initialization
 ***/

int Tetromino::reset( int color )
{
    color_ = color;

    for( int i=0; i<4; i++ ){
        blocks_[i].x = TETROMINO_X0 + Tetrominos[color-1][i][X] * TILE_SIZE;
        blocks_[i].y = TETROMINO_Y0 + Tetrominos[color-1][i][Y] * TILE_SIZE;

        if( gameMatrix_.getCell( blocks_[i] ) ) return -1;
    }

    pivotPoint_.x = TETROMINO_X0;
    pivotPoint_.y = TETROMINO_Y0;

    return 0;
}


/***
 * 3. Updating
 ***/

int Tetromino::moveHorizontally( const int& cells )
{
    const int dx = cells << TILE_SIZE_2;
    PixelPos auxPos;

    for( int i=0; i<4; i++ ){
        auxPos.x = blocks_[i].x + dx;
        auxPos.y = blocks_[i].y;

        if( gameMatrix_.getCell( auxPos ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i].x += dx;
    }

    pivotPoint_.x += dx;

    return 0;
}


int Tetromino::rotate()
{
    PixelPos dstBlocks[4];

    for( int i=0; i<4; i++ ){
        dstBlocks[i].x = -blocks_[i].y + pivotPoint_.y + pivotPoint_.x;
        dstBlocks[i].y = blocks_[i].x - pivotPoint_.x + pivotPoint_.y + TILE_SIZE;

        if( gameMatrix_.getCell( dstBlocks[i] ) ){
                return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i] = dstBlocks[i];
    }

    return 0;
}


int Tetromino::fall( const int& dy )
{
    PixelPos auxPos;

    for( int i=0; i<4; i++ ){
        auxPos.x = blocks_[i].x;
        auxPos.y = blocks_[i].y + dy;

        if( gameMatrix_.getCell( auxPos ) )
        {
            fixToGameMatrix();
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i].y += dy;
    }
    pivotPoint_.y += dy;

    return 0;
}


void Tetromino::fixToGameMatrix()
{
    gameMatrix_.print();

    for( int j=0; j<4; j++ ){
        gameMatrix_.setCell( blocks_[j], color_ );
    }

    gameMatrix_.print();
}


/***
 * 4. Drawing
 ***/

int Tetromino::draw( SDL_Renderer* renderer )
{
    SDL_Rect srcRect = { (Sint16)(color_<<TILE_SIZE_2), 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };
    SDL_Rect dstRect = { 0, 0, (Sint16)TILE_SIZE, (Sint16)TILE_SIZE };

    for( int i=0; i<4; i++ ){
        if( blocks_[i].y >= 2 ){
            dstRect.x = MATRIX_X+(blocks_[i].x);
            dstRect.y = MATRIX_Y+(blocks_[i].y-2);
            if( SDL_RenderCopy( renderer, texture_, &srcRect, &dstRect ) < 0 ) return -1;
        }
    }

    return 0;
}
