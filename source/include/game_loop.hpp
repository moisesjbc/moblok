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
#include <matrix.hpp>


/*                                        Global constants                                     */
/***********************************************************************************************/


/*                                        Type declarations                                    */
/***********************************************************************************************/

enum GRAPHICS {
    TILESET = 0,
    SCORE,
    NEXT_TETROMINO,
    PAUSE_TEXT,
    N_GRAPHICS
};

enum RECTS {
    SCORE_RECT_1 = 0,
    SCORE_RECT_2,
    NEXT_TETROMINO_RECT,
    PAUSE_TEXT_RECT,
    N_RECTS
};

const int INITIAL_LOCK_TIME = 250;


/*
    NOTE : All the methods  of this class that returns a value returns 0 if they succeded.
    Otherwise they return -1.
*/

class GameLoop {
    private:
        Player player_;

        SDL_Window *screen_;
        SDL_Renderer* renderer_;

        //tr::TextRenderer* textRenderer;
        SDL_Texture* graphics_[N_GRAPHICS];
        SDL_Rect rects_[N_RECTS];

        unsigned int lockTime_;

        Matrix matrix_;

    public:
        /***************************************************************************************/
        /*                            1. Inicialization and destruction.                       */
        /***************************************************************************************/
        GameLoop( SDL_Window *screen, SDL_Renderer* renderer, const ResourceLoader* resourceLoader )    throw( const char* );
        ~GameLoop()                         throw();
        void NewGame()                  throw();

        /***************************************************************************************/
        /*                             2. GameLoop loop's related functions.                       */
        /***************************************************************************************/
        int MainLoop()  throw();
        void Update()   throw();
        void Pause( bool& exitGame ) throw();

        /***************************************************************************************/
        /*                                 3. Graphic functions.                               */
        /***************************************************************************************/
        int Draw()      throw();
        int DrawGUI()   throw();

        /***************************************************************************************/
        /*                                4. Auxiliar functions.                               */
        /***************************************************************************************/
    private:
        void SetEventsState( int state ) const throw();
};

#endif
// GAME_HPP
