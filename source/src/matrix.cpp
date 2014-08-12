
/*                                             Includes                                        */
/***********************************************************************************************/

#include <matrix.hpp>
#include <iostream>


/*                                        Global constants                                     */
/***********************************************************************************************/

char errorMsg[151] = "\0";

/*                                         Type definitions                                    */
/***********************************************************************************************/


/***
 * 1. Construction
 ***/

Matrix::Matrix()
{
    reset();
}


/***
 * 2. Initialization
 ***/

void Matrix::reset()
{
    unsigned int row, column;

    for( row = 0; row < N_MATRIX_ROWS; row++ ){
        for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
            cells_[row][column] = 0;
        }
    }
}


/***
 * 3. Cells management
 ***/


int Matrix::getCell( PixelPos pos ) const
{
    CUint row = pos.y >> TILE_SIZE_2;
    CUint column = pos.x >> TILE_SIZE_2;

    if( ( row < N_MATRIX_ROWS) && ( column < (N_MATRIX_COLUMNS ) ) ){
        return cells_[row][column];
    }else{
        return -1;
    }
}


void Matrix::setCell( PixelPos pos, CUint& cell )
{
    CUint row = pos.y >> TILE_SIZE_2;
    CUint column = pos.x >> TILE_SIZE_2;

    if( ( row < N_MATRIX_ROWS ) && ( column < (N_MATRIX_COLUMNS) ) && ( cell < N_COLORS ) ){
        cells_[row][column] = cell;
    }
}

/***
 * 4. Updating
 ***/

// TODO: Remove these arguments and check only the rows affected by the last
// fixed tetrominos.
int Matrix::eraseCompletedRows( int firstRow, int lastRow )
{
    int res = 0;
    int currentRow;

    for( currentRow = firstRow; currentRow <= lastRow; ){
        if( eraseRowIfCompleted( currentRow ) == 0 ){
            res++;
            //currentRow++;
        }else{
            currentRow++;
        }
    }
    return res;
}


/***
 * 5. Drawing
 ***/

int Matrix::draw( SDL_Renderer* renderer, SDL_Texture* tileset )
{
    unsigned int row, column;

    SDL_Rect srcRect_ = {0, 0, TILE_SIZE, TILE_SIZE};
    SDL_Rect dstRect_ = {MATRIX_X, MATRIX_Y, TILE_SIZE, TILE_SIZE};
    for( row = FIRST_VISIBLE_ROW; row < N_MATRIX_ROWS; row++ ){
        for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
            srcRect_.x = cells_[row][column] << TILE_SIZE_2;
            SDL_RenderCopy( renderer, tileset, &srcRect_, &dstRect_ );
            dstRect_.x += TILE_SIZE;
        }
        dstRect_.x = MATRIX_X;
        dstRect_.y += TILE_SIZE;
    }

    return 0;
}


void Matrix::print()
{
    unsigned int row, column;

    std::cout << "Matrix::Print()" << std::endl
              << "-----------------------------------------------" << std::endl;
    for( row = 0; row < N_MATRIX_ROWS; row++ ){
        std::cout << "row(" << row << "): ";
        for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
            std::cout << cells_[row][column] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------------" << std::endl;
}


/***
 * 6. Updating (private)
 ***/

int Matrix::eraseRowIfCompleted( const int& rowToBeChecked )
{
    unsigned int row, column = 0;

    // Check if the given row is completed.
    for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
        if( !cells_[rowToBeChecked][column] ){
            return -1;
        }
    }

    // The given row is completed, delete it by making the above rows to
    // "fall".
    for( row = rowToBeChecked; row >= FIRST_VISIBLE_ROW; row-- ){
        for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
            cells_[row][column] = cells_[row-1][column];
        }
    }

    return 0;
}
