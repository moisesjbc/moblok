
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
    { 677, 100, 160, 26 },  // LINES_RECT,
    { 677, 136, 160, 26 },  // LEVEL_RECT
    { 677, 172, 160, 160 }  // NEXT_TETROMINO_RECT
};


/*                                       Type definitions                                      */
/***********************************************************************************************/


/***
 * 1. Construction
 ***/

GameLoop::GameLoop( SDL_Window *screen, SDL_Renderer* renderer, const ResourceLoader* resourceLoader ) :
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


/***
 * 2. Destruction
 ***/

GameLoop::~GameLoop()
{
    for( int i=0; i<N_GRAPHICS; i++ ){
        SDL_DestroyTexture( graphics_[i] );
    }
}


/***
 * 3. Execution
 ***/

void GameLoop::run()
{
    newGame();

    runMainLoop();
}

/***
 * 3. Initialization
 ***/

void GameLoop::newGame()
{
    player_.reset();
    matrix_.reset();
}


/***
 * 4. Updating
 ***/

int GameLoop::runMainLoop()
{
    SDL_Event event;
    lockTime_ = INITIAL_LOCK_TIME;
    Uint32 t0, t1;
    bool exitGame = false;

    // Draws the matrix and GUI.
    draw();

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
                                currentTetromino_.moveHorizontally( -1 );
                            break;
                            case SDLK_RIGHT:
                                currentTetromino_.moveHorizontally( 1 );
                            break;
                            case SDLK_UP:
                                currentTetromino_.rotate();
                            break;
                            case SDLK_DOWN:
                                currentTetromino_.fall();
                            break;
                            case SDLK_ESCAPE:
                                pause( exitGame );
                            break;
                            default:
                            break;
                        }

                    break;
                    case SDL_WINDOWEVENT:
                        draw();
                    break;
                    case SDL_QUIT:
                        exitGame = true;
                    break;
                    default:
                    break;

                }
            }


            t1 = SDL_GetTicks();
        }while( t1-t0 < REFRESH_TIME );

        // Logic update.
        updateLogic();

        // Display.
        draw();
    }

    return 0;
}


void GameLoop::updateLogic()
{
    int erasedLines = 0;

    // FIXME: With big dy, sometimes the tetromino looks "broken" while
    // falling.
    if( currentTetromino_.fall( 4 + player_.level_ ) < 0 ){
        erasedLines = matrix_.eraseCompletedRows();
        player_.score_ += 2;
        if( erasedLines ){
            matrix_.draw( renderer_, graphics_[TILESET] );
            SDL_RenderPresent( renderer_ );
            player_.filledLines_ += erasedLines;
            player_.score_ += 10*erasedLines;

            if( player_.score_ >= ( player_.level_ * 10 ) ){ // TODO: Do I make higher levels larger?
                player_.level_++;
                lockTime_ -= 10;
            }
        }
        player_.gameOver_ = (currentTetromino_.reset( player_.nextTetromino_ ) == -1);
        player_.nextTetromino_ = (rand()%7)+1;

        drawGUI();
    }
}


void GameLoop::pause( bool& exitGame )
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


/***
 * 5. Drawing
 ***/

int GameLoop::drawGUI()
{
    SDL_Rect dstRect = rects[SCORE_RECT_1];
    char panelString[32];
    SDL_Color fontColor = { 0, 0, 0, 0 };
    SDL_Surface* panelSurface = nullptr;
    SDL_Texture* panelTexture = nullptr;
    unsigned int i;


    unsigned int textRectsIndices[] =
        { SCORE_RECT_1, LINES_RECT, LEVEL_RECT };
    char formatStrings[][32] =
    {
        "Score: %u",
        "Lines: %u",
        "Level: %u"
    };
    unsigned int* varPointers[] =
    {
        &( player_.score_ ),
        &( player_.filledLines_ ),
        &( player_.level_ )
    };

    for( i = 0; i < 3; i++ ){
        dstRect = rects[textRectsIndices[i]];

        // Draw the text panel.
        SDL_RenderCopy( renderer_, graphics_[SCORE], nullptr, &dstRect );

        // Draw the text
        sprintf( panelString, formatStrings[i], *( varPointers[i] ) );
        panelSurface = TTF_RenderText_Solid( font_, panelString, fontColor );
        panelTexture = SDL_CreateTextureFromSurface( renderer_, panelSurface );
        dstRect.x = dstRect.x + ( dstRect.w - panelSurface->w ) / 2;
        dstRect.y = dstRect.y + ( dstRect.h - panelSurface->h ) / 2;
        dstRect.w = panelSurface->w;
        dstRect.h = panelSurface->h;
        SDL_RenderCopy( renderer_, panelTexture, nullptr, &dstRect );
        SDL_FreeSurface( panelSurface );
        SDL_DestroyTexture( panelTexture );
    }

    // Draws the next Tetromino;
    SDL_Rect srcRect = { (Sint16)((player_.nextTetromino_-1)*160), 0, 160, 160 };
    dstRect = rects[NEXT_TETROMINO_RECT];
    return SDL_RenderCopy( renderer_, graphics_[NEXT_TETROMINO], &srcRect, &dstRect );
}


int GameLoop::draw()
{
    // Clear screen with background color.
    SDL_SetRenderDrawColor( renderer_, 20, 171, 180, 255);
    SDL_RenderClear( renderer_ );

    // Draw the GUI
    drawGUI();

    // Draw the game matrix.
    matrix_.draw( renderer_, graphics_[TILESET] );

    currentTetromino_.draw( renderer_ );

    SDL_RenderPresent( renderer_ );

    return 0;
}
