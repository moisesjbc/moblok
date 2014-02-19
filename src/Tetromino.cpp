
#include "Tetromino.hpp"

/*                                       Type decfinitions                                     */
/***********************************************************************************************/


/*                                       1. Initialization                                     */


Tetromino::Tetromino( Matrix &matrix, const int& x, const int& y ) : x0_(x), y0_(y), matrix_(&matrix)
{
    New();
}


/*                                      2. Tetromino movement.                                 */

int Tetromino::Move( const int& dx )
{

}







/*                                            3. Miscellaneous                                 */


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

}
