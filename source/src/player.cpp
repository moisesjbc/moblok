
/*                                             Includes                                        */
/***********************************************************************************************/

#include <player.hpp>
#include <cstdlib>

/*                                        Global constants                                     */
/***********************************************************************************************/



/*                                       Type decfinitions                                     */
/***********************************************************************************************/


/***
 * 1. Construction
 ***/

Player::Player()
    : level_(1), score_(0), filledLines_(0), gameOver_(0)
{
    // TODO: Call Reset()?
    nextTetromino_ = (rand()%7)+1;
}


/***
 * 2. Initialization
 ***/

void Player::reset()
{
    level_ = 1;
    score_ = filledLines_ = gameOver_ = 0;
    nextTetromino_ = (rand()%7)+1;
}

