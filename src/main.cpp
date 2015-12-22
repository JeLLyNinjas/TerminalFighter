#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
extern "C" {
    #include <SDL.h>
    #include <SDL_ttf.h>
}
#include <stdio.h>
#include <unistd.h>
#include <SDL_ttf.h>
#include <SDL2/SDL.h>

#include "delay.h"

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1232

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

void close();
bool quit;


bool init_SDL()
{
    //Initializes SDL
    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    //Creates the SDL Window
    window = SDL_CreateWindow("Video Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Creates the renderer. 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
        printf("Creating a software renderer instead\n");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (renderer == NULL)
        {
            printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
            return false;                    
            //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
    return true;
}

void processEvents()
{
    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    printf("SDL_QUIT was called\n");
                    close();
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            printf("Esc was Pressed!\n");
                            close();
                            break;
                        case SDLK_LEFT:
                            printf("Left arrow was Pressed!\n");
                            break;
                        case SDLK_RIGHT:
                            printf("Right arrow was Pressed!\n");
                            break;
                        case SDLK_UP:
                            break;
                        case SDLK_DOWN:
                            break;
                        case SDLK_SPACE:
                            printf("Space was pressed!\n");
                    }
            }
        }
}

/* Cleans up and should free everything used in the program*/
void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
    exit(0);
}



int main(int argc, char* argv[])
{
    if (!init_SDL()){
        fprintf(stderr, "Could not initialize SDL!\n");
        return -1;
    }

    if (TTF_Init() != 0){
        fprintf(stderr, "TTF Init failed! %s\n", TTF_GetError());
        return -1;
    }

    //Render red filled quad
    int x = 0; 


    Delay delayer(false);
    while (!quit)
    {

        if (x > SCREEN_HEIGHT - 1)
            x = 0;
        x++;

        processEvents();

        //Draw blue horizontal line
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( renderer, &fillRect );

        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );        
        SDL_RenderDrawLine( renderer, 0, x, SCREEN_WIDTH, x );

        SDL_Surface *frame_rate_surface = delayer.grab_frame_rate();
        SDL_Texture *frame_rate_texture = SDL_CreateTextureFromSurface( renderer, frame_rate_surface);
        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 0;  //controls the rect's x coordinate 
        Message_rect.y = 0; // controls the rect's y coordinte
        Message_rect.w = 200; // controls the width of the rect
        Message_rect.h = 70; // controls the height of the rect
        SDL_RenderCopy( renderer, frame_rate_texture, NULL, &Message_rect);
        SDL_FreeSurface(frame_rate_surface);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );        
        SDL_RenderClear(renderer);

        delayer.delay_with_fps(60);

    }

    return 0;
}



