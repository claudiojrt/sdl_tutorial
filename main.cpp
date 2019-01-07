#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Textures", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 100, 255);

    IMG_Init(IMG_INIT_PNG);

    bool quit = false;
    SDL_Event e;

    gTexture = loadTexture("texture.png");

    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer);

    }

    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
    return 0;
}

SDL_Texture* loadTexture(std::string path) {

    SDL_Surface* image = IMG_Load(path.c_str());
    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 255, 255));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, image);

    return  texture;
}