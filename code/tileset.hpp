#pragma once

#include <SDL.h>
#include "texture.hpp"
#include <string>
#include <vector>

class Tileset
{
    public:
        Tileset();
        ~Tileset();

        void loadFromFile(SDL_Renderer* renderer, std::string path, int columns, int rows);
        void render(SDL_Rect camera, int tile, SDL_Rect pos);

    private:
        SDL_Renderer* mRenderer;
        Texture mTexture;
        std::vector<SDL_Rect> mTiles;
};