#include <SDL.h>
#include <SDL_image.h>
#include <helper.hpp>
#include <player.hpp>
#include <level.hpp>

//Function definitions
void Init();
void Quit();
void CameraMove();

//Global objects
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Joystick* gJoystick = NULL;
SDL_Rect gCamera = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};

//Player
Player player1;

//Global flags and control variables
std::vector<SDL_Rect> gObjects;
SDL_Event gEvent;
bool gQuit = false;

int main(int argc, char *argv[])
{
    Init();

    player1.setPos(350, 100);
    player1.idle.loadFromFile(gRenderer, "assets/spritesheets/Clob_spritesheet.png", 4, 10);
    player1.idle.mTimer.start();
    player1.jump.loadFromFile(gRenderer, "assets/spritesheets/Clob_jump.png", 4, 5);

    Level level1(1);
    level1.loadTileset(gRenderer, "assets/tilesets/mainTileset.png", 5, 1);
    gObjects = level1.getColliders();

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

        if(gJoystick == NULL)
        {
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if(currentKeyStates[SDL_SCANCODE_A])
                player1.moveLeft();
            if(currentKeyStates[SDL_SCANCODE_D])
                player1.moveRight();
            if(!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
                player1.stopMove();
        }
        

        //Clear the back buffer
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 80, 80, 80, 255);

        //Fetch the new position
        player1.move(gObjects);

        //Adjust the camera
        CameraMove();

        //Render everything
        level1.Render(gCamera);
        player1.render(gCamera);

        //Bring back buffer to front
        SDL_RenderPresent(gRenderer);
    }
    
    Quit();
    //system("pause");
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
    gCamera.x = (player1.getPosX() + player1.idle.getWidth() / 2) - SCREEN_WIDTH/2;
    gCamera.y = (player1.getPosY() + player1.idle.getHeight() / 2) - SCREEN_HEIGHT/2;

    if(gCamera.x < 0)
        gCamera.x = 0;
    if(gCamera.y < 0)
        gCamera.y = 0;
    if(gCamera.x > LEVEL_WIDTH - gCamera.w)
        gCamera.x = LEVEL_WIDTH - gCamera.w;
    if(gCamera.y > LEVEL_HEIGHT - gCamera.h)
        gCamera.y = LEVEL_HEIGHT - gCamera.h;
}