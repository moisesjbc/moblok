/*
    Module      : Gane
    Author      : Moisés J. Bonilla Caraballo
    Description : Main class which defines the game engine.
*/

#ifndef GAME_HPP
#define GAME_HPP

/*                                             Includes                                        */
/***********************************************************************************************/

#include <resource_loader.hpp>
#include <player.hpp>
#include <tetromino.hpp>
#include <matrix.hpp>


/*                                        Global constants                                     */
/***********************************************************************************************/


/*                                        Type declarations                                    */
/***********************************************************************************************/

enum GRAPHICS {
    TILESET = 0,
    SCORE,
    NEXT_TETROMINO,
    PAUSE_MENU,
    N_GRAPHICS
};

enum RECTS {
    SCORE_RECT_1 = 0,
    LINES_RECT,
    NEXT_TETROMINO_RECT,
    N_RECTS
};

const unsigned int REFRESH_TIME = 33; // 33 ms ~ 30 fps.

const int INITIAL_LOCK_TIME = 250;

class GameLoop {
    public:
        /***
         * 1. Construction
         ***/
        GameLoop( SDL_Window *screen, SDL_Renderer* renderer, const ResourceLoader* resourceLoader );


        /***
         * 2. Destruction
         ***/
        ~GameLoop();


        /***
         * 3. Execution
         ***/
        void run();


    private:
        /***
         * 4. Initialization
         ***/
        void newGame();


        /***
         * 5. Main loop execution
         ***/
        int runMainLoop();
        void updateLogic();
        void pause( bool& exitGame );


        /***
         * 5. Drawing
         ***/
        int draw();
        int drawGUI();


    private:
        Player player_;

        SDL_Window *screen_;
        SDL_Renderer* renderer_;

        SDL_Texture* graphics_[N_GRAPHICS];
        SDL_Rect rects_[N_RECTS];

        unsigned int lockTime_;

        Matrix matrix_;
        Tetromino currentTetromino_;

        TTF_Font* font_;
};

#endif
// GAME_HPP
