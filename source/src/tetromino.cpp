
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
    pos_.x = TETROMINO_X0;
    pos_.y = TETROMINO_Y0;

    for( int i=0; i<4; i++ ){
        blocks_[i].x = pos_.x + Tetrominos[color-1][i][X];
        blocks_[i].y = pos_.y + Tetrominos[color-1][i][Y];

        if( gameMatrix_.getCell( blocks_[i].x, blocks_[i].y ) ) return -1;
    }

    return 0;
}


/***
 * 3. Updating
 ***/

int Tetromino::moveHorizontally( const int& dx )
{
    for( int i=0; i<4; i++ ){
        if( gameMatrix_.getCell( blocks_[i].x + dx, blocks_[i].y ) ){
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i].x += dx;
    }
    pos_.x += dx;

    return 0;
}


int Tetromino::rotate()
{
    for( int i=0; i<4; i++ ){
        int aux_x = blocks_[i].x;

        if( gameMatrix_.getCell( pos_.x - (blocks_[i].y-pos_.y) - 1, pos_.y + (aux_x-pos_.x) ) ){
                return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        int aux_x = blocks_[i].x;
        blocks_[i].x = pos_.x - (blocks_[i].y-pos_.y) - 1;
        blocks_[i].y = pos_.y + (aux_x-pos_.x);
    }

    return 0;
}


int Tetromino::fall( const int& dy )
{
    for( int i=0; i<4; i++ ){
        if( gameMatrix_.getCell( blocks_[i].x, blocks_[i].y + dy )  )
        {
            fixToGameMatrix();
            return -1;
        }
    }

    for( int i=0; i<4; i++ ){
        blocks_[i].y += dy;
    }
    pos_.y += dy;

    return 0;
}


void Tetromino::fixToGameMatrix()
{
    gameMatrix_.print();

    for( int j=0; j<4; j++ ){
        gameMatrix_.setCell( blocks_[j].x, blocks_[j].y, color_ );
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
            dstRect.x = MATRIX_X+(blocks_[i].x<<TILE_SIZE_2);
            dstRect.y = MATRIX_Y+((blocks_[i].y-2)<<TILE_SIZE_2);
            if( SDL_RenderCopy( renderer, texture_, &srcRect, &dstRect ) < 0 ) return -1;
        }
    }

    return 0;
}
