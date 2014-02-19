
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
        music_ = Mix_LoadMUS( "data/music/tetris1.mid" );
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
    while(1){

        MainMenu();
        game_->NewGame();
    }
}

void Tetris::MainMenu()
{
    SDL_Surface *background_ = IMG_Load( "data/img/menu_background.png" );
    il::ButtonsGroup buttons(2);
    Uint32 t0, t1;
    SDL_Event event;
    int aux = 0;

    try{
        buttons.LoadButton( 39, 490, "data/img/bLudi.png" );
        buttons.LoadButton( 39, 550, "data/img/bEliri.png" );
    }catch( ... ){
        strcpy( errorMsg, "MainMenu::Error - Unable to load button" );
        throw errorMsg;
    }

    Mix_PlayMusic( music_, -1 );


    SDL_BlitSurface( background_, NULL, screen_, NULL );
    SDL_FreeSurface( background_ );

    SDL_Flip( screen_ );
    t0 = SDL_GetTicks();
    for( ; ; ){
        t1 = t0;
        do{
            if( SDL_PollEvent( &event ) ){
                aux = buttons.HandleEvent( event );
                if( aux >= 0 ){
                    switch( aux ){
                        case 0:
                            return;
                        break;
                        case 1:
                            exit(0);
                        break;
                        default:
                        break;
                    }
                }else{
                    switch( event.type ){
                        case SDL_QUIT:
                            exit(0);
                        break;
                    }
                }
            }
            t1 = SDL_GetTicks();
        }while( t1-t0 < 10 );

        buttons.DrawIfNeeded( screen_ );
        SDL_Flip( screen_ );
    }
}
