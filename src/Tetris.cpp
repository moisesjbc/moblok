
/*                                             Includes                                        */
/***********************************************************************************************/

#include"Tetris.hpp"

/*                                        Global constants                                     */
/***********************************************************************************************/




/*                                       Type definitions                                      */
/***********************************************************************************************/

/*                               1. Inicialization and destruction                             */

Tetris::Tetris() throw( const char* )
{
    try{
        screen_ = SDL_SetVideoMode( RES_X, RES_Y, 8, SDL_ANYFORMAT );
        game_ = new Game( screen_ );
        music_ = Mix_LoadMUS( "data/music/Tetris_theme.ogg" );
        if( !music_ ){
            throw Mix_GetError();
        }
    }catch( const char* ){
        throw;
    }
}

Tetris::~Tetris(){
    SDL_FreeSurface( screen_ );
    Mix_FreeMusic( music_ );
    delete game_;
}


/*                                       2. Other functions                                    */

void Tetris::Start()
{
    SDL_Surface *background_ = NULL;
    SDL_Event event;
    bool playGame = false;
    bool exitGame = false;

    // Start playing music.
    Mix_PlayMusic( music_, -1 );

    while( !exitGame ){
        // Load the main menu background and display it.
        background_ = IMG_Load( "data/img/menu_background.png" );
        SDL_BlitSurface( background_, NULL, screen_, NULL );
        SDL_Flip( screen_ );

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
        SDL_FreeSurface( background_ );

        // Start the game if player wants to.
        if( playGame ){
            game_->NewGame();
        }
    }
}

