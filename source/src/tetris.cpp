
/*                                             Includes                                        */
/***********************************************************************************************/

#include <config.hpp>
#include <tetris.hpp>
#include <iostream>
#include <cassert>

/*                                        Global constants                                     */
/***********************************************************************************************/




/*                                       Type definitions                                      */
/***********************************************************************************************/

/***
 * 1. Construction
 ***/

Tetris::Tetris() :
    resourceLoader_( { DATA_INSTALL_DIR, DATA_SOURCE_DIR } )
{
    try{
        screen_ = SDL_CreateWindow( "Moblok'",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    RES_X,
                                    RES_Y,
                                    0 );
        renderer_ = SDL_CreateRenderer( screen_, -1, 0);

        // TODO: Add checks;

        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
        SDL_RenderSetLogicalSize( renderer_, RES_X, RES_Y );


        game_ = new GameLoop( screen_, renderer_, &resourceLoader_ );

        music_ = resourceLoader_.loadMusic( "Tetris_theme.ogg" );
    }catch( const char* ){
        throw;
    }
}


/***
 * 2. Destruction
 ***/

Tetris::~Tetris(){
    SDL_DestroyWindow( screen_ );
    SDL_DestroyRenderer( renderer_ );
    Mix_FreeMusic( music_ );
    delete game_;
}


/***
 * 3. Initialization
 ***/

void Tetris::start()
{
    SDL_Texture* background_ = nullptr;
    SDL_Event event;
    bool playGame = false;
    bool exitGame = false;

    // Start playing music.
    Mix_PlayMusic( music_, -1 );

    while( !exitGame ){
        // Load the main menu background and display it.
        background_ = resourceLoader_.loadImage( "menu_background.png", renderer_ );
        SDL_RenderCopy( renderer_, background_, nullptr, nullptr );
        SDL_RenderPresent( renderer_ );

        // Initialize the available options: play the game or exit it.
        playGame = false;
        exitGame = false;

        // Wait for user to decide if he/she plays or exits the game.
        do{
            SDL_WaitEvent( &event );

            switch( event.type ){
                case SDL_KEYDOWN:
                    if( event.key.keysym.sym == SDLK_RETURN ){
                        playGame = true;
                    }else if( event.key.keysym.sym == SDLK_ESCAPE ){
                        exitGame = true;
                    }
                break;
                case SDL_QUIT:
                    exitGame = true;
                break;
            }
        }while( !playGame && !exitGame );

        // Free resources.
        SDL_DestroyTexture( background_ );

        // Start the game if player wants to.
        if( playGame ){
            game_->run();
        }
    }
}

