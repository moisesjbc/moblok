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

#ifndef TETRIS_HPP
#define TETRIS_HPP

/*                                        Type declarations                                    */
/***********************************************************************************************/

struct Player {
    int score;
    int filledLines;
    Player() : score(0), filledLines(0) {}
    void Clear(){ score = filledLines = 0; }
};

class Tetris {
    private:
        Tetromino *currentTetromino_;
        Matrix *matrix_;
        SDL_Surface *surface_, *tileset_;

        int gameOver;

    public:
        Tetris( SDL_Surface *surface, const unsigned int& x, const unsigned int& y, const unsigned int& w,
                const unsigned int& h );
        ~Tetris();
        void NewGame();
        void NewGame( const unsigned int& x, const unsigned int& y, const unsigned int& w,
                        const unsigned int& h );

        void Update();

        int GameEnd();
        int GameLoop();


        int Draw();
};

#endif
// TETRIS_HPP
