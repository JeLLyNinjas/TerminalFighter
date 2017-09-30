#include <map>
#include <unistd.h>
#include <memory>

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
extern "C" {
#include <SDL.h>
#include <SDL_ttf.h>
}
#include <SDL_ttf.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>
#include <glog/logging.h>

#include "GameState/I_GameState.h"
#include "GameStateHandler/GameStateHandler.h"

#include "TestState/TestState.h"
#include "MenuState/MenuState.h"
#include "GameConstants/GameConstants.h"

SDL_Renderer* main_renderer = NULL;
SDL_Window* window = NULL;
bool quit;

bool init_SDL();
void processEvents();
void close();
bool init_SDL() {
    int numdrivers = SDL_GetNumRenderDrivers ();
    LOG(INFO) << "Render driver count: " << numdrivers;

    for (int i = 0; i < numdrivers; i++) {
        SDL_RendererInfo drinfo;
        SDL_GetRenderDriverInfo (0, &drinfo);
        LOG(INFO) << "Driver name (" << i << "): " << drinfo.name;

        if (drinfo.flags & SDL_RENDERER_SOFTWARE) {
            LOG(INFO) << "The main_renderer is a software fallback";
        }

        if (drinfo.flags & SDL_RENDERER_ACCELERATED) {
            LOG(INFO) << "The main_renderer uses hardware acceleration";
        }

        if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC) {
            LOG(INFO) << "Tresent is synchronized with the refresh rate";
        }

        if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE) {
            LOG(INFO) << "The main_renderer supports rendering to texture";
        }
    }

    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    //Initializes SDL
    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0) {
        LOG(ERROR) << "SDL could not initialize! SDL Error: " << SDL_GetError();
        return false;
    }

    //Creates the SDL Window
    window = SDL_CreateWindow("Video Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        LOG(ERROR) << "Window could not be created! SDL Error: " << SDL_GetError();
        return false;
    }

    LOG(INFO) << "Driver: " <<  SDL_GetCurrentVideoDriver();
    //Creates the main_renderer.
    main_renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (main_renderer == NULL) {
        LOG(WARNING) << "Renderer could not be created. SDL_Error: " << SDL_GetError();
        LOG(WARNING) << "Creating a software main_renderer instead";
        main_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

        if (main_renderer == NULL) {
            LOG(ERROR) << "Renderer could not be created. SDL_Error: " << SDL_GetError();
            return false;
            //SDL_SetRenderDrawColor(main_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }

    return true;
}

/* Cleans up and should free everything used in the program*/
void close() {
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    main_renderer = NULL;
    SDL_Quit();
    exit(0);
}

int main(int argc, char* argv[]) {
#ifdef __linux__
    system("mkdir /tmp/TerminalFighter/");
    FLAGS_log_dir = "/tmp/TerminalFighter";
#endif

    SDL_version compile_version;
    const SDL_version* link_version = Mix_Linked_Version();
    SDL_MIXER_VERSION(&compile_version);
    printf("compiled with SDL_mixer version: %d.%d.%d\n",
           compile_version.major,
           compile_version.minor,
           compile_version.patch);
    printf("running with SDL_mixer version: %d.%d.%d\n",
           link_version->major,
           link_version->minor,
           link_version->patch);


    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Logging Intialized INFO";

    if (!init_SDL()) {
        LOG(FATAL) << "Could not initialize SDL!";
    }

    if (TTF_Init() != 0) {
        LOG(FATAL) << "TTF Init failed! " << TTF_GetError();
    }

    std::unique_ptr<I_GameState> test_state(new TestState(*main_renderer));
    std::unique_ptr<I_GameState> menu_state(new MenuState(*main_renderer));
    std::vector<I_GameState*> gamestates;
    gamestates.push_back(test_state.get());
    gamestates.push_back(menu_state.get());
    GameStateHandler gs_handler = GameStateHandler(gamestates);
    gs_handler.start(gamestates::MAIN_MENU);
    close();
    return 0;
}
