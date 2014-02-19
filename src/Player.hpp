/*
    Module      : Player
    Author      : Moisés J. Bonilla Caraballo
    Description : Struct defined in order to manage all player's info and statistics.
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

/*                                             Includes                                        */
/***********************************************************************************************/

#include"Matrix.hpp"

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

    Matrix matrix_;

    /*******************************************************************************************/
    /*                                    1. Inicialization                                    */
    /*******************************************************************************************/
    Player();

    /*******************************************************************************************/
    /*                                    2. Other functions                                   */
    /*******************************************************************************************/
    void Reset();
};



#endif
// PLAYER_HPP
