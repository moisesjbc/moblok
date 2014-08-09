
/*                                             Includes                                        */
/***********************************************************************************************/

#include <config.hpp>
#include <game_loop.hpp>
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
    "pause_menu.png"            // PAUSE_MENU
};

const SDL_Rect rects[4] = {
    { 677, 64, 160, 26 },   // SCORE_RECT_1
    { 753, 67, 80, 21 },    // SCORE_RECT_2
    { 677, 100, 160, 160 }  // NEXT_TETROMINO_RECT
};


/*                                       Type definitions                                      */
/***********************************************************************************************/


/***********************************************************************************************/
/*                               1. Inicialization and destruction.                            */
/***********************************************************************************************/

GameLoop::GameLoop( SDL_Window *screen, SDL_Renderer* renderer, const ResourceLoader* resourceLoader ) throw( const char* ) :
    screen_(screen),
    renderer_( renderer ),
    graphics_{ nullptr },
    currentTetromino_( resourceLoader, renderer, matrix_ )
{
    try{
        screen_ = screen;

        for( int i=0; i<N_GRAPHICS; i++ ){
            graphics_[i] = resourceLoader->loadImage( graphicsPaths[i], renderer_ );
        }

        font_ = resourceLoader->loadFont( "LiberationSans-Bold.ttf", 20 );

    }catch( const char* ){
        throw;
    }catch( std::bad_alloc& ){
        strcpy( errorMsg, "GameLoop::Error - Memory cant be allocated" );
        throw errorMsg;
    }
}

GameLoop::~GameLoop() throw()
{
    for( int i=0; i<N_GRAPHICS; i++ ){
        SDL_DestroyTexture( graphics_[i] );
    }
}


void GameLoop::NewGame() throw()
{
    // Ignore all events except SDL_QUIT, SDL_KEYDOWN and SDL_VIDEOEXPOSE.
    SetEventsState( SDL_IGNORE );
    SDL_EventState( SDL_QUIT, SDL_ENABLE );
    SDL_EventState( SDL_KEYDOWN, SDL_ENABLE );
    SDL_EventState( SDL_WINDOWEVENT, SDL_ENABLE );

    player_.Reset();
    matrix_.Reset();
    MainLoop();

    // Enable all the events.
    SetEventsState( SDL_ENABLE );
}


/***********************************************************************************************/
/*                                   2. GameLoop loop's related functions.                     */
/***********************************************************************************************/

int GameLoop::MainLoop() throw()
{
    SDL_Event event;
    lockTime_ = INITIAL_LOCK_TIME;
    Uint32 t0, t1;
    bool exitGame = false;

    // Draws the matrix and GUI.
    Draw();

    // GameLoop loop
    while( !exitGame && !player_.gameOver_ ){

        t0 = SDL_GetTicks();
        do{
            // Handle input.
            if( SDL_PollEvent( &event ) ){

                switch( event.type ){
                    case SDL_KEYDOWN:

                        switch( event.key.keysym.sym ){
                            case SDLK_LEFT:
                                currentTetromino_.MoveTetromino( -1 );
                            break;
                            case SDLK_RIGHT:
                                currentTetromino_.MoveTetromino( 1 );
                            break;
                            case SDLK_UP:
                                currentTetromino_.RotateTetromino();
                            break;
                            case SDLK_DOWN:
                                currentTetromino_.TetrominoFall();
                            break;
                            case SDLK_ESCAPE:
                                //Mix_PauseMusic();
                                Pause( exitGame );
                                //Mix_ResumeMusic();
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
        }while( t1-t0 < INITIAL_LOCK_TIME /*REFRESH_TIME*/ );

        // Logic update.
        Update();

        // Display.
        Draw();
    }

    return 0;
}


void GameLoop::Update() throw()
{
    int erasedLines = 0;

    if( currentTetromino_.TetrominoFall() < 0 ){
        erasedLines = matrix_.EraseLines(  );
        if( erasedLines ){
            matrix_.Draw( renderer_, graphics_[TILESET] );
            SDL_RenderPresent( renderer_ );
            player_.filledLines_ += erasedLines;
            player_.score_ += 10*erasedLines;

            if( player_.filledLines_ >= player_.level_*10 ){
                player_.score_ += 100;
                player_.level_++;
                lockTime_ -= 10;
            }
        }
        player_.gameOver_ = (currentTetromino_.Reset( player_.nextTetromino_ ) == -1);
        player_.nextTetromino_ = (rand()%7)+1;

        DrawGUI();
    }
}


void GameLoop::Pause( bool& exitGame ) throw()
{
    SDL_Event event;
    bool exitPauseMenu = false;
    int pauseMenuWidth, pauseMenuHeight;

    SDL_QueryTexture( graphics_[PAUSE_MENU],
                      nullptr,
                      nullptr,
                      &pauseMenuWidth,
                      &pauseMenuHeight );

    SDL_Rect pauseMenuRect = {
        (RES_X - pauseMenuWidth ) >> 1,
        (RES_Y - pauseMenuHeight ) >> 1,
        pauseMenuWidth,
        pauseMenuHeight
    };

    SDL_RenderCopy( renderer_, graphics_[PAUSE_MENU], nullptr, &pauseMenuRect );
    SDL_RenderPresent( renderer_ );


    while( !exitPauseMenu ){
        // Keep waiting until player press a valid key.
        SDL_WaitEvent( &event );

        // Process user event.
        if( event.type == SDL_QUIT ){
            exitGame = true;
        }else if( event.type == SDL_KEYDOWN ){
            SDL_Keycode key = event.key.keysym.sym;

            if( key == SDLK_ESCAPE || ( key == SDLK_1 ) ){
                exitPauseMenu = true;
            }else if( key == SDLK_2 ){
                if( Mix_PausedMusic() ){
                    Mix_ResumeMusic();
                }else{
                    Mix_PauseMusic();
                }
            }else if( key == SDLK_3 ){
                exitPauseMenu = true;
                exitGame = true;
            }
        }
    }
}


/***********************************************************************************************/
/*                                       3. Graphic functions.                                 */
/***********************************************************************************************/


int GameLoop::DrawGUI() throw()
{
    SDL_Rect dstRect = rects[SCORE_RECT_1];
    char scoreString[32];
    SDL_Surface* scoreSurface = nullptr;
    SDL_Color scoreColor = { 0, 0, 0, 0 };
    SDL_Texture* scoreTexture = nullptr;

    // Draw the score panel.
    SDL_RenderCopy( renderer_, graphics_[SCORE], nullptr, &dstRect );

    // Draw the score.
    sprintf( scoreString, "%012i", player_.score_ );
    scoreSurface = TTF_RenderText_Solid( font_, scoreString, scoreColor );
    scoreTexture = SDL_CreateTextureFromSurface( renderer_, scoreSurface );
    dstRect.x = dstRect.x + ( dstRect.w - scoreSurface->w ) / 2;
    dstRect.y = dstRect.y + ( dstRect.h - scoreSurface->h ) / 2;
    dstRect.w = scoreSurface->w;
    dstRect.h = scoreSurface->h;
    SDL_RenderCopy( renderer_, scoreTexture, nullptr, &dstRect );
    SDL_FreeSurface( scoreSurface );
    SDL_DestroyTexture( scoreTexture );

    // Draws the next Tetromino;
    SDL_Rect srcRect = { (Sint16)((player_.nextTetromino_-1)*160), 0, 160, 160 };
    dstRect = rects[NEXT_TETROMINO_RECT];
    return SDL_RenderCopy( renderer_, graphics_[NEXT_TETROMINO], &srcRect, &dstRect );
}


int GameLoop::Draw() throw()
{
    // Clear screen with background color.
    SDL_SetRenderDrawColor( renderer_, 20, 171, 180, 255);
    SDL_RenderClear( renderer_ );

    // Draw the GUI
    DrawGUI();

    // Draw the game matrix.
    matrix_.Draw( renderer_, graphics_[TILESET] );

    currentTetromino_.Draw( renderer_ );

    SDL_RenderPresent( renderer_ );

    return 0;
}


/***********************************************************************************************/
/*                                       4. Auxiliar functions.                                */
/***********************************************************************************************/

void GameLoop::SetEventsState( int state ) const throw()
{
    (void)( state ); // TODO: Reimplement this.
    /*
    for( int i=0; i<SDL_NUMEVENTS; i++ ){
        SDL_EventState( i, state );
    }
    */
}
