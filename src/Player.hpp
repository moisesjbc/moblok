/*
    Module      :
    Author      :
    Description :
*/


/*                                             Includes                                        */
/***********************************************************************************************/

#include"Tetromino.hpp"

/*                                        Global constants                                     */
/***********************************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

/*                                        Type declarations                                    */
/***********************************************************************************************/

struct Player {
    int level;
    int score;
    int filledLines;

    Matrix *matrix;
    Tetromino *tetromino;

    // 1. Inicialization
    Player();
    void ResetScore();
    void Clear();
};



#endif
// PLAYER_HPP
