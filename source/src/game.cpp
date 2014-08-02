
/*                                             Includes                                        */
/***********************************************************************************************/

#include <config.hpp>
#include <game.hpp>
#include <iostream>

/*                                        Global constants                                     */
/***********************************************************************************************/

const SDL_Color blackColor = {0,0,0,0};

#define PROJ_BUILD_DIR_DEFINE "${PROJECT_BINARY_DIR}"
#define PROJ_SOURCE_DIR_DEFINE "${CMAKE_HOME_DIRECTORY}"

const char graphicsPaths[4][70] = {
    "tileset.png",	 			// TILESET
    "score.png",        		// SCORE
    "next_tetromino.png",       // NEXT_TETROMINO
    "pause_text.png"            // PAUSE_TEXT
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

Game::Game( SDL_Window *screen, SDL_Renderer* renderer, const ResourceLoader* resourceLoader ) throw( const char* ) :
    screen_(screen),
    renderer_( renderer ),
    graphics_{ nullptr }
{
    try{
        screen_ = screen;

        for( int i=0; i<N_GRAPHICS; i++ ){
            graphics_[i] = resourceLoader->loadImage( graphicsPaths[i], renderer_ );
        }

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
        SDL_DestroyTexture( graphics_[i] );
    }
}


void Game::NewGame() throw()
{
    // Ignore all events except SDL_QUIT, SDL_KEYDOWN and SDL_VIDEOEXPOSE.
    SetEventsState( SDL_IGNORE );
    SDL_EventState( SDL_QUIT, SDL_ENABLE );
    SDL_EventState( SDL_KEYDOWN, SDL_ENABLE );
    SDL_EventState( SDL_WINDOWEVENT, SDL_ENABLE );

    player_.Reset();
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

    // Game loop
    while( !exitGame && !player_.gameOver_ ){

        t0 = SDL_GetTicks();
        do{
            // Handle input.
            if( SDL_PollEvent( &event ) ){

                switch( event.type ){
                    case SDL_KEYDOWN:

                        switch( event.key.keysym.sym ){
                            case SDLK_LEFT:
                                if( !player_.matrix_.MoveTetromino( -1 ) ){
                                    player_.matrix_.DrawTetromino( renderer_, graphics_[TILESET] );
                                }
                            break;
                            case SDLK_RIGHT:
                                if( !player_.matrix_.MoveTetromino( 1 ) ){
                                    player_.matrix_.DrawTetromino( renderer_, graphics_[TILESET] );
                                }
                            break;
                            case SDLK_UP:
                                if( !player_.matrix_.RotateTetromino() ){
                                    player_.matrix_.DrawTetromino( renderer_, graphics_[TILESET] );
                                }
                            break;
                            case SDLK_DOWN:
                                if( !player_.matrix_.TetrominoFall() ){
                                    player_.matrix_.DrawTetromino( renderer_, graphics_[TILESET] );
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
                    case SDL_WINDOWEVENT:
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
        Draw();
        SDL_RenderPresent( renderer_ );
    }

    return 0;
}


void Game::Update() throw()
{
    int erasedLines = 0;

    if( player_.matrix_.TetrominoFall() < 0 ){
        erasedLines = player_.matrix_.EraseLines();
        if( erasedLines ){
            player_.matrix_.Draw( renderer_, graphics_[TILESET] );
            SDL_RenderPresent( renderer_ );
            player_.filledLines_ += erasedLines;
            player_.score_ += 10*erasedLines;

            if( player_.filledLines_ >= player_.level_*10 ){
                player_.score_ += 100;
                player_.level_++;
                lockTime_ -= 10;
            }
        }
        player_.gameOver_ = (player_.matrix_.NewTetromino( player_.nextTetromino_ ) == -1);
        player_.nextTetromino_ = (rand()%7)+1;

        DrawGUI();
    }
}


void Game::Pause( bool& exitGame ) throw()
{
    SDL_Event event;
    SDL_Rect dstRect = rects[PAUSE_TEXT_RECT];

    SDL_RenderCopy( renderer_, graphics_[PAUSE_TEXT], nullptr, &dstRect );

    SDL_RenderPresent( renderer_ );

    // Keep waiting until player press a key.
    do {
        SDL_WaitEvent( &event );
    }while( ( event.type != SDL_QUIT ) && ( event.type != SDL_KEYDOWN ) );

    // Check if user wants to exit game instead of resume it.
    exitGame = ( event.type == SDL_QUIT )
                || ( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_F1 ) );
}


/***********************************************************************************************/
/*                                       3. Graphic functions.                                 */
/***********************************************************************************************/


int Game::DrawGUI() throw()
{
    // Draw the score panel.
    SDL_Rect dstRect = rects[SCORE_RECT_1];
    SDL_RenderCopy( renderer_, graphics_[SCORE], nullptr, &dstRect );

    // Draws the next Tetromino;
    SDL_Rect srcRect = { (Sint16)((player_.nextTetromino_-1)*160), 0, 160, 160 };
    dstRect = rects[NEXT_TETROMINO_RECT];
    return SDL_RenderCopy( renderer_, graphics_[NEXT_TETROMINO], &srcRect, &dstRect );
}


int Game::Draw() throw()
{
    // Clear screen with background color.
    SDL_SetRenderDrawColor( renderer_, 20, 171, 180, 255);
    SDL_RenderClear( renderer_ );

    // Draw the GUI
    DrawGUI();

    // Draw the game matrix.
    player_.matrix_.Draw( renderer_, graphics_[TILESET] );

    SDL_RenderPresent( renderer_ );

    return 0;
}


/***********************************************************************************************/
/*                                       4. Auxiliar functions.                                */
/***********************************************************************************************/

void Game::SetEventsState( int state ) const throw()
{
    (void)( state ); // TODO: Reimplement this.
    /*
    for( int i=0; i<SDL_NUMEVENTS; i++ ){
        SDL_EventState( i, state );
    }
    */
}
