#include "code/global.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <texture.h>
#include <player.h>

//Function definitions
void Init();
void Quit();
void CameraMove();

//Global.h definitionss
extern int LEVEL_WIDTH = 2000;
extern int LEVEL_HEIGHT = 600;
extern const int SCREEN_WIDTH = 800;
extern const int SCREEN_HEIGHT = 600;
extern const int FALL_VELOCITY = 1;
extern const int JOYSTICK_DEAD_ZONE = 14000;

//Global objects
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Joystick* gJoystick = NULL;
SDL_Rect gCamera = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
Player player1;

//Global flags and control variables
std::vector<SDL_Rect> gObjects;
SDL_Event gEvent;
bool gQuit = false;

int main(int argc, char *argv[])
{
    Init();

    Texture background;
        background.loadFromFile(gRenderer, "res/background.png", 1, 0);
    Texture ground;
        ground.loadFromFile(gRenderer, "res/ground-tile.png", 1, 0);

    gObjects.push_back({0, 535, 2000, 100});

    player1.setPos(350, 100);
    player1.sprite.loadFromFile(gRenderer, "res/Clob_spritesheet.png", 4, 10);
    player1.sprite.mTimer.start();
    player1.jump.loadFromFile(gRenderer, "res/Clob_jump.png", 4, 4);

    while(!gQuit)
    {
        while(SDL_PollEvent(&gEvent) != 0)
        {
            if(gEvent.type == SDL_QUIT)
            {
                gQuit = true;
            }

            player1.handleEvent(gEvent);
        }

        //Clear the back buffer
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 80, 80, 80, 255);

        //Fetch the new positions
        player1.move(gObjects);

        //Adjust the camera
        CameraMove();

        //Render everything
        for(int i = 0; i < 3; i++)
            background.render(gRenderer, 960 * i, 0, 0, gCamera, 2.5);
    
        for(int i = 0; i < 7; i++)
            ground.render(gRenderer, 320 * i, 465, 0, gCamera, 2.5);

        player1.render(gRenderer, gCamera);

        //Bring back buffer to front
        SDL_RenderPresent(gRenderer);
    }
    
    Quit();
    return 0;
}

//Init SDL systems
void Init()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    gWindow = SDL_CreateWindow("CJ engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(SDL_NumJoysticks() > 0)
    {
        gJoystick = SDL_JoystickOpen(0);
    }

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

    SDL_JoystickClose(gJoystick);
    gJoystick = NULL;

    IMG_Quit();
    SDL_Quit();
}

void CameraMove()
{
    gCamera.x = (player1.getPosX() + player1.sprite.getWidth() / 2) - SCREEN_WIDTH/2;
    gCamera.y = (player1.getPosY() + player1.sprite.getHeight() / 2) - SCREEN_HEIGHT/2;

    if(gCamera.x < 0)
        gCamera.x = 0;
    if(gCamera.y < 0)
        gCamera.y = 0;
    if(gCamera.x > LEVEL_WIDTH - gCamera.w)
        gCamera.x = LEVEL_WIDTH - gCamera.w;
    if(gCamera.y > LEVEL_HEIGHT - gCamera.h)
        gCamera.y = LEVEL_HEIGHT - gCamera.h;
}