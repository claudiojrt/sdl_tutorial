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

Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;

int main(int argc, char *argv[])
{
    Init();

    Texture clob;
    Texture stonebrick;
    clob.loadFromFile(gRenderer, "res/Clob_spritesheet.png", 4, 10);
    stonebrick.loadFromFile(gRenderer, "res/stone_brick.png", 1, 0);

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            //On keypress change rgb values
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_a:
                        clob.setFlipMode(SDL_FLIP_HORIZONTAL);
                        break;
                    case SDLK_d:
                        clob.setFlipMode(SDL_FLIP_NONE);
                        break;
                    case SDLK_q:
                        clob.setRotationAngle(clob.getRotationAngle() - 30);
                        break;
                    case SDLK_e:
                        clob.setRotationAngle(clob.getRotationAngle() + 30);
                        break;
                }
            }
        }

        //Clear the back buffer
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);

        //Render everything
        clob.setColor(r,g,b);
        clob.render(gRenderer, 350, 408, clob.mCounter / clob.getAnimationSpeed());
        for (int i = 1; i < 8; i++) {
            stonebrick.render(gRenderer, i * stonebrick.getWidth() - stonebrick.getWidth(), SCREEN_HEIGHT - stonebrick.getHeight(), 0);
        }

        clob.mCounter++;
        if(clob.mCounter / clob.getAnimationSpeed() >= clob.getFrames())
            clob.mCounter = 0;

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
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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