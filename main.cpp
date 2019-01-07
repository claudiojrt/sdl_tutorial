#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <texture.h>
#include <cmath>

//Function definitions
void Init();
void Quit();

//Global references and buffers
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int JOYSTICK_DEAD_ZONE = 14000;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Joystick* gJoystick = NULL;
SDL_Haptic* gJoystickHaptic = NULL;

SDL_Event e;
bool quit = false;
bool pToggle = false;

Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;

int main(int argc, char *argv[])
{
    Init();

    Texture clob;
    Texture stonebrick;
    clob.loadFromFile(gRenderer, "res/Clob_spritesheet.png", 4, 10);
    clob.mTimer.start();

    stonebrick.loadFromFile(gRenderer, "res/stone_brick.png", 1, 0);

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }

            else if(e.type == SDL_JOYAXISMOTION)
            {
                if(e.jaxis.which == 0)
                {
                    // X axis
                    if(e.jaxis.axis == 0)
                    {
                        if(e.jaxis.value < -JOYSTICK_DEAD_ZONE)
                            clob.mXDir = -1;
                        else if(e.jaxis.value > JOYSTICK_DEAD_ZONE)
                            clob.mXDir = 1;
                        else
                            clob.mXDir = 0;
                    }

                    // Y axis
                    else if(e.jaxis.axis == 1)
                    {
                        if(e.jaxis.value < -JOYSTICK_DEAD_ZONE)
                            clob.mYDir = -1;
                        else if(e.jaxis.value > JOYSTICK_DEAD_ZONE)
                            clob.mYDir = 1;
                        else
                            clob.mYDir = 0;
                    }
                if(clob.mXDir != 0 || clob.mYDir != 0)
                    clob.setRotationAngle(atan2((double)clob.mYDir, (double)clob.mXDir) * (180.0 / M_PI));
                }
            }

            else if(e.type == SDL_JOYBUTTONDOWN)
            {
                SDL_HapticRumblePlay(gJoystickHaptic, 0.75, 300);
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if(currentKeyStates[SDL_SCANCODE_P] && !pToggle)
        {
            pToggle = true;
            if(clob.mTimer.isPaused())
            {
                clob.mTimer.start();
            }
            else
            {
                clob.mTimer.pause();
            }
        }
        else if (!currentKeyStates[SDL_SCANCODE_P])
        {
            pToggle = false;
        }

        /* if(currentKeyStates[SDL_SCANCODE_D])
            clob.setFlipMode(SDL_FLIP_NONE);
            clob.setFlipMode(SDL_FLIP_HORIZONTAL);

        if(currentKeyStates[SDL_SCANCODE_Q])
           clob.setRotationAngle(clob.getRotationAngle() - 30);

        if(currentKeyStates[SDL_SCANCODE_E])
            clob.setRotationAngle(clob.getRotationAngle() + 30); */

        //Clear the back buffer
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);

        //Render everything
        clob.setColor(r,g,b);

        if(clob.mTimer.isRunning())
            clob.setColor(clob.mTimer.getTicks() / 5, clob.mTimer.getTicks() / 5, clob.mTimer.getTicks() / 5);
            
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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC );
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow("Texture Class", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(SDL_NumJoysticks() > 0)
    {
        gJoystick = SDL_JoystickOpen(0);
        gJoystickHaptic = SDL_HapticOpenFromJoystick(gJoystick);
        SDL_HapticRumbleInit(gJoystickHaptic);
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

    SDL_HapticClose(gJoystickHaptic);
    gJoystickHaptic = NULL;

    SDL_JoystickClose(gJoystick);
    gJoystick = NULL;

    IMG_Quit();
    SDL_Quit();
}