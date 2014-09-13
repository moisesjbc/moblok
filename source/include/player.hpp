/*
    Module      : Player
    Author      : Moisés J. Bonilla Caraballo
    Description : Struct defined in order to manage all player's info and statistics.
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

/*                                             Includes                                        */
/***********************************************************************************************/


/*                                        Global constants                                     */
/***********************************************************************************************/


/*                                        Type declarations                                    */
/***********************************************************************************************/

struct Player {
    /***
     * 1. Construction
     ***/
    Player();


    /***
     * 2. Initialization
     ***/
    void reset();


    unsigned int level_;
    unsigned int score_;
    unsigned int filledLines_;
    unsigned int gameOver_;
    unsigned int nextTetromino_;
};



#endif
// PLAYER_HPP
