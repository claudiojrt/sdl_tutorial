#include <iostream>
#include <string>
#include <SDL.h>

const int screenWidht = 1280;
const int screenHeight = 720;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gStretchedSurface = NULL;

bool gQuit = false;

SDL_Surface *loadTexture(std::string path);
void init();
void close();

int main(int argc, char *args[])
{
    SDL_Event event;
    SDL_Surface *helloWorld = NULL;
    SDL_Rect stretchRect;

    bool xDirection = true, yDirection = true;
    int cX = 35, cY = 49;

    init();

    // CARREGAR IMAGEM DE FORMA OTIMIZADA
    helloWorld = loadTexture("res/helloWorld.bmp");

    // GAME LOOP
    while (!gQuit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                gQuit = true;
            }
        }

        if (xDirection) {
            if (cX++ + helloWorld->w > screenWidht) {
                xDirection = !xDirection;
            }
        }
        else {
            if (cX-- == 0) {
                xDirection = !xDirection;
            }
        }

        if (yDirection) {
            if (cY++ + helloWorld->h > screenHeight) {
                yDirection = !yDirection;
            }
        }
        else {
            if (cY-- == 0) {
                yDirection = !yDirection;
            }
        }

        stretchRect.x = cX;
        stretchRect.y = cY;
        stretchRect.w = helloWorld->w;
        stretchRect.h = helloWorld->h;

        SDL_BlitScaled( helloWorld, NULL, gScreenSurface, &stretchRect );
        //SDL_BlitSurface(helloWorld, NULL, gScreenSurface, NULL);

        SDL_UpdateWindowSurface(gWindow);
        SDL_Delay(5);
    }

    // FINALIZAÇÃO
    SDL_FreeSurface(helloWorld);
    helloWorld = NULL;

    close();

    return 0;
}

void init()
{
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Screen saver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidht, screenHeight, SDL_WINDOW_SHOWN);
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 255, 255, 255));
}

void close()
{
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

SDL_Surface *loadTexture(std::string path)
{
    SDL_Surface *optimizedTexture = NULL;
    SDL_Surface *textureLoader = SDL_LoadBMP(path.c_str());

    optimizedTexture = SDL_ConvertSurface(textureLoader, gScreenSurface->format, NULL);
    SDL_FreeSurface(textureLoader);

    return optimizedTexture;
}