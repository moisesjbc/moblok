
/*                                             Includes                                        */
/***********************************************************************************************/

#include"Game.hpp"

/*                                        Global constants                                     */
/***********************************************************************************************/

const SDL_Color blackColor = {0,0,0,0};

const char graphicsPaths[4][70] = {
    "data/img/tileset.png",             // TILESET
    "data/img/score.png",               // SCORE
    "data/img/next_tetromino.png",      // NEXT_TETROMINO
    "data/img/pause_text.png"           // PAUSE_TEXT
};

const SDL_Rect rects[4] = {
    { 677, 64, 160, 26 },   // SCORE_RECT_1
    { 753, 67, 80, 21 },    // SCORE_RECT_2
    { 677, 100, 160, 160 }, // NEXT_TETROMINO_RECT
    { 365, 100, 0, 0 }      // PAUSE_TEXT
};


/*                                       Type definitions                                      */
/***********************************************************************************************/


/***********************************************************************************************/
/*                               1. Inicialization and destruction.                            */
/***********************************************************************************************/

Game::Game( SDL_Surface *screen ) throw( const char* ) : screen_(screen)
{
    try{
        screen_ = screen;

        for( int i=0; i<N_GRAPHICS; i++ ){
            graphics_[i] = IMG_Load( graphicsPaths[i] );
            if( !graphics_[i] ){
                strcpy( errorMsg, "Game::Error - Unable to load resource [" );
                strcat( errorMsg, graphicsPaths[i] );
                strcat( errorMsg, "]" );
                throw errorMsg;
            }
        }

        player_ = new Player();

    }catch( const char* ){
        throw;
    }catch( std::bad_alloc& ){
        strcpy( errorMsg, "Game::Error - Memory cant be allocated" );
        throw errorMsg;
    }
}

Game::~Game() throw()
{
    for( int i=0; i<N_GRAPHICS; i++ ){
        SDL_FreeSurface( graphics_[i] );
    }
    delete player_;
}


void Game::NewGame() throw()
{
    // Ignore all events except SDL_QUIT, SDL_KEYDOWN and SDL_VIDEOEXPOSE.
    SetEventsState( SDL_IGNORE );
    SDL_EventState( SDL_QUIT, SDL_ENABLE );
    SDL_EventState( SDL_KEYDOWN, SDL_ENABLE );
    SDL_EventState( SDL_VIDEOEXPOSE, SDL_ENABLE );

    SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

    SDL_FillRect( screen_, NULL, SDL_MapRGB( screen_->format, 20, 171, 180 ) );

    player_->Reset();
    GameLoop();

    // Enable all the events.
    SetEventsState( SDL_ENABLE );
}


/***********************************************************************************************/
/*                                   2. Game loop's related functions.                         */
/***********************************************************************************************/

int Game::GameLoop() throw()
{
    SDL_Event event;
    lockTime_ = INITIAL_LOCK_TIME;
    Uint32 t0, t1;
    bool exitGame = false;

    // Draws the matrix and GUI.
    Draw();
    SDL_Flip( screen_ );

    // Game loop
    while( !exitGame && !player_->gameOver_ ){

        t0 = SDL_GetTicks();
        do{
            // Handle input.
            if( SDL_PollEvent( &event ) ){

                switch( event.type ){
                    case SDL_KEYDOWN:

                        switch( event.key.keysym.sym ){
                            case SDLK_LEFT:
                                if( !player_->matrix_.MoveTetromino( -1 ) ){
                                    player_->matrix_.DrawTetromino( screen_, graphics_[TILESET] );
                                    SDL_Flip( screen_ );
                                }
                            break;
                            case SDLK_RIGHT:
                                if( !player_->matrix_.MoveTetromino( 1 ) ){
                                    player_->matrix_.DrawTetromino( screen_, graphics_[TILESET] );
                                    SDL_Flip( screen_ );
                                }
                            break;
                            case SDLK_UP:
                                if( !player_->matrix_.RotateTetromino() ){
                                    player_->matrix_.DrawTetromino( screen_, graphics_[TILESET] );
                                    SDL_Flip( screen_ );
                                }
                            break;
                            case SDLK_DOWN:
                                if( !player_->matrix_.TetrominoFall() ){
                                    player_->matrix_.DrawTetromino( screen_, graphics_[TILESET] );
                                    SDL_Flip( screen_ );
                                }
                            break;
                            case SDLK_ESCAPE:
                                Mix_PauseMusic();
                                Pause( exitGame );
                                Mix_ResumeMusic();
                                Draw();
                            break;
                            default:
                            break;
                        }

                    break;
                    case SDL_VIDEOEXPOSE:
                        Draw();
                    break;
                    case SDL_QUIT:
                        exitGame = true;
                    break;
                    default:
                    break;

                }
            }


            t1 = SDL_GetTicks();
        }while( t1-t0 < lockTime_ );

        // Logic update.
        Update();

        // Display.
        player_->matrix_.DrawTetromino( screen_, graphics_[TILESET] );
        SDL_Flip( screen_ );
    }

    return 0;
}


void Game::Update() throw()
{
    int erasedLines = 0;

    if( player_->matrix_.TetrominoFall() < 0 ){
        erasedLines = player_->matrix_.EraseLines();
        if( erasedLines ){
            player_->matrix_.Draw( screen_, graphics_[TILESET] );
            SDL_Flip( screen_ );
            player_->filledLines_ += erasedLines;
            player_->score_ += 10*erasedLines;

            if( player_->filledLines_ >= player_->level_*10 ){
                player_->score_ += 100;
                player_->level_++;
                lockTime_ -= 10;
            }
        }
        player_->gameOver_ = (player_->matrix_.NewTetromino( player_->nextTetromino_ ) == -1);
        player_->nextTetromino_ = (rand()%7)+1;

        DrawGUI();
    }
}


void Game::Pause( bool& exitGame ) throw()
{
    SDL_Event event;
    SDL_Rect dstRect = rects[PAUSE_TEXT_RECT];

    SDL_BlitSurface( graphics_[PAUSE_TEXT], NULL, screen_, &dstRect );

    SDL_Flip( screen_ );

    // Keep waiting until player press a key.
    do {
        SDL_WaitEvent( &event );
    }while( ( event.type != SDL_QUIT ) && ( event.type != SDL_KEYDOWN ) );

    // Check if user wants to exit game instead of resume it.
    exitGame = ( event.type == SDL_QUIT )
                || ( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ) );
}


/***********************************************************************************************/
/*                                       3. Graphic functions.                                 */
/***********************************************************************************************/


int Game::DrawGUI() throw()
{
    // Draws the next Tetromino;
    SDL_Rect srcRect = { (Uint16)((player_->nextTetromino_-1)*160), 0, 160, 160 };
    SDL_Rect dstRect = rects[NEXT_TETROMINO_RECT];
    return SDL_BlitSurface( graphics_[NEXT_TETROMINO], &srcRect, screen_, &dstRect );
}


int Game::Draw() throw()
{
    SDL_Rect dstRect = rects[SCORE_RECT_1];
    SDL_BlitSurface( graphics_[SCORE], NULL, screen_, &dstRect );
    DrawGUI();
    player_->matrix_.Draw( screen_, graphics_[TILESET] );
    player_->matrix_.DrawTetromino( screen_, graphics_[TILESET] );

    return 0;
}


/***********************************************************************************************/
/*                                       4. Auxiliar functions.                                */
/***********************************************************************************************/

void Game::SetEventsState( int state ) const throw()
{
    for( int i=0; i<SDL_NUMEVENTS; i++ ){
        SDL_EventState( i, state );
    }
}
