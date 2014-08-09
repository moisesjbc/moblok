
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

void Matrix::SetCell( CUint& x, CUint& y, CUint& cell )
{
    if( ( y < N_MATRIX_ROWS ) && ( x < (N_MATRIX_COLUMNS) ) && ( cell < N_COLORS ) ){
        cells_[y][x] = cell;
    }
}

int Matrix::GetCell( CUint& x, CUint& y ) const
{
    if( ( y < N_MATRIX_ROWS) && ( x < (N_MATRIX_COLUMNS ) ) ){
        return cells_[y][x];
    }else{
        return -1;
    }
}

void Matrix::Reset() throw()
{
    unsigned int row, column;

    for( row = 0; row < N_MATRIX_ROWS; row++ ){
        for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
            cells_[row][column] = 0;
        }
    }
}


/***********************************************************************************************/
/*                                         4. Matrix update                                    */
/***********************************************************************************************/

int Matrix::EraseLine( const int& rowToBeChecked ) throw()
{
    unsigned int row, column = 0;

    // Check if the given row is completed.
    std::cout << "rowToBeChecked: " << rowToBeChecked << std::endl;
    for( column = 0; column < N_MATRIX_COLUMNS; column++ ){
        if( !cells_[rowToBeChecked][column] ){
            std::cout << "\t\t(" << rowToBeChecked << ", " << column << ") is empty" << std::endl;
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



int Matrix::EraseLines( int firstRow, int lastRow ) throw()
{
    int res = 0;
    int currentRow;

    for( currentRow = firstRow; currentRow > lastRow; ){
        std::cout << "Checking row: " << currentRow << std::endl;
        if( EraseLine( currentRow ) == 0 ){
            res++;
            //currentRow++;
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
