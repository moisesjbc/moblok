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
    int level_;
    int score_;
    int filledLines_;
    int gameOver_;
    int nextTetromino_;

    /***
     * 1. Construction
     ***/
    Player();


    /***
     * 2. Initialization
     ***/
    void Reset();
};



#endif
// PLAYER_HPP
