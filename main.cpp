#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;
SDL_Event *event;

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load(filename.c_str());
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "PNG test", NULL );

    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( image );

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Initialize
    if( init() == false )
    {
        return 1;
    }

    SDL_Surface* images[4];
    image = load_image("vida.png");
    images[0]=load_image( "run01.png" );
    images[1]=load_image( "run02.png" );
    images[2]=load_image( "run03.png" );
    images[3]=load_image( "run04.png" );

    int a=50;
    int b=50;
    bool cont = true;
    int x=0;
    while(cont){

        if(x>3){
            x=0;
        }
        //If there was a problem in loading the image
        if( images == NULL )
        {
            return 1;
        }

        SDL_Event event;
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
//                quit = true;
                cont = false;
            }
        }

        Uint8 *keystates = SDL_GetKeyState( NULL );

        if(keystates[SDLK_RIGHT]){
            a += 10;
        }

        if(keystates[SDLK_LEFT]){
            a -= 10;
        }

        if(keystates[SDLK_UP]){
            b -= 10;
        }

        if(keystates[SDLK_DOWN]){
            b += 10;
        }

        //Apply the surface to the screen
        apply_surface(0,0, image,screen);
        apply_surface( a, b, images[x], screen );

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }





        //Wait 2 seconds
        SDL_Delay( 20 );

        x++;
    }
    //Free the surface and quit SDL
    clean_up();

    return 0;
}
