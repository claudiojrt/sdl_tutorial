#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <texture.h>

//Function definitions
void Init();
void Quit();

//Global references and buffers
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Event e;
bool quit = false;

int main(int argc, char *argv[])
{
    Init();

    Texture clob;
    Texture stonebrick;
    clob.loadFromFile(gRenderer, "res/Clob_spritesheet.png", 4);
    stonebrick.loadFromFile(gRenderer, "res/stone_brick.png", 1);

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        //Clear the back buffer
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);

        //Render everything
        clob.render(gRenderer, 350, 408, clob.mCounter);
        for (int i = 1; i < 8; i++) {
            stonebrick.render(gRenderer, i * stonebrick.getWidth() - stonebrick.getWidth(), SCREEN_HEIGHT - stonebrick.getHeight(), 0);
        }

        clob.mCounter++;
        if(clob.mCounter == 4)
            clob.mCounter = 0;

        if(clob.mCounter % 2 == 0){
            SDL_Delay(300);
        }
        else{
            SDL_Delay(100);
        }

        //Bring back buffer to front
        SDL_RenderPresent(gRenderer);
    }
    
    Quit();
    return 0;
}

//Init SDL systems
void Init()
{
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Texture Class", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_PNG);
}

//Quit SDL systems and free resources
void Quit()
{
    //Destroy textures

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}