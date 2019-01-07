#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

int gScreenWidth = 800;
int gScreenHeight = 600;

SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;

bool gQuit = false;

//Functions

SDL_Surface* loadSurface(std::string path);

int main(int argc, char* args[]) {

    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("PNG Loader",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gScreenWidth, gScreenHeight, SDL_WINDOW_SHOWN);
    gSurface = SDL_GetWindowSurface(gWindow);
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface* pngImage = NULL;
    pngImage = loadSurface("loaded.png");
    if (pngImage == NULL){
        std::cout << "Error";
    }

    SDL_Event e;

    while(!gQuit) {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                gQuit = true;
            }
        }

        SDL_BlitScaled(pngImage, NULL, gSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
    }

    //Free loaded image
	SDL_FreeSurface(pngImage);
	pngImage = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
    gSurface = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

    return 0;
}

SDL_Surface* loadSurface(std::string path) {

    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    optimizedSurface = SDL_ConvertSurface(loadedSurface, gSurface->format, NULL);
    SDL_FreeSurface(loadedSurface);

    return optimizedSurface;
}