
/*                                             Includes                                        */
/***********************************************************************************************/

#include"Tetris.hpp"

/*                                        Global constants                                     */
/***********************************************************************************************/

const Uint32 LOCK_TIME = 200;
const Uint32 WAIT_TIME = 25;


/*                                       Type decfinitions                                     */
/***********************************************************************************************/

Tetris::Tetris( SDL_Surface *surface, const unsigned int& x, const unsigned int& y, const unsigned int& w,
        const unsigned int& h ) : surface_(surface), tileset_(0), gameOver(0)
{
    try{
        tileset_ = IMG_Load( "tileset.png" );
        matrix_ = new Matrix( x, y, w, h );
        currentTetromino_ = new Tetromino( *matrix_, (w >> 1), 1 );
        if( !tileset_ ) throw std::runtime_error( "Tetris::Error - Tileset not found" );
    }catch( std::runtime_error& ){
        throw;
    }catch( std::bad_alloc& ){
        throw std::runtime_error( "Tetris::Error - Memory cant be allocated" );
    }
}

Tetris::~Tetris(){
    SDL_FreeSurface( tileset_ );
    delete currentTetromino_;
    delete matrix_;
}


void Tetris::NewGame()
{
    currentTetromino_->New();
    matrix_->Clear();
}

void Tetris::NewGame( const unsigned int& x, const unsigned int& y, const unsigned int& w,
            const unsigned int& h )
{
    currentTetromino_->New();
    try{
        matrix_ = new Matrix( x, y, w, h );
    }catch( std::runtime_error& ){
        throw;
    }
}


int Tetris::GameEnd(){
    return 1;
}

void Tetris::Update()
{
    int minY, maxY;
    if( currentTetromino_->Fall() < 0 ){
        currentTetromino_->GetRange( minY, maxY );
        if( matrix_->EraseLines( minY, maxY ) ){
            matrix_->Draw( surface_, tileset_ );
            SDL_Flip( surface_ );
        }
        gameOver = !currentTetromino_->New();
    }
};

int Tetris::GameLoop(){
    SDL_Event event;
    int userInput = 1;
    Uint32 t0, t1;

    SDL_EventState( SDL_ACTIVEEVENT, SDL_IGNORE);
    SDL_EventState( SDL_KEYUP, SDL_IGNORE);

    SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState( SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    SDL_EventState( SDL_MOUSEBUTTONUP, SDL_IGNORE);

    SDL_EventState( SDL_JOYAXISMOTION, SDL_IGNORE);
    SDL_EventState( SDL_JOYBALLMOTION, SDL_IGNORE);
    SDL_EventState( SDL_JOYHATMOTION, SDL_IGNORE);
    SDL_EventState( SDL_JOYBUTTONDOWN, SDL_IGNORE);
    SDL_EventState( SDL_JOYBUTTONUP, SDL_IGNORE);

    SDL_EventState( SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState( SDL_VIDEORESIZE, SDL_IGNORE);
    SDL_EventState( SDL_VIDEOEXPOSE, SDL_IGNORE);
    SDL_EventState( SDL_USEREVENT, SDL_IGNORE);

    while( !gameOver ){

        t0 = SDL_GetTicks();
        do{
            // Handle input.
            if( SDL_PollEvent( &event ) ){

                switch( event.type ){
                    case SDL_KEYDOWN:

                        switch( event.key.keysym.sym ){
                            case SDLK_LEFT:
                                currentTetromino_->Move( -1 );
                                userInput = 1;
                            break;
                            case SDLK_RIGHT:
                                currentTetromino_->Move( 1 );
                                userInput = 1;
                            break;
                            case SDLK_UP:
                                currentTetromino_->Rotate();
                                userInput = 1;
                            break;
                            default:
                            break;
                        }

                    break;

                    case SDL_QUIT:
                        return -1;
                    break;
                    default:
                    break;

                }


                if( userInput ){
                    currentTetromino_->Draw( surface_, tileset_ );
                    SDL_Delay(WAIT_TIME);
                    SDL_Flip( surface_ );
                    userInput = 0;
                }

            }

            t1 = SDL_GetTicks();
        }while( t1-t0 < LOCK_TIME );

        while( SDL_PollEvent(&event) ){
            if( event.type == SDL_QUIT ){
                return -1;
            }
        }

        SDL_EventState( SDL_KEYDOWN, SDL_IGNORE);

        SDL_Delay(WAIT_TIME);

        // Logic update.
        Update();

        // Display.
        currentTetromino_->Draw( surface_, tileset_ );
        SDL_Flip( surface_ );


        SDL_EventState( SDL_KEYDOWN, SDL_ENABLE);
    }

    std::cout << "Fin del juego!" << std::endl;
    SDL_Delay(5000);
    return 0;
}


int Tetris::Draw()
{
    //currentTetromino_->Draw( *matrix_ );
    return matrix_->Draw( surface_, tileset_ );
}
