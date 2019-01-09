#pragma once

#include <SDL.h>
#include <tileset.hpp>
#include <tile.hpp>
#include <helper.hpp>
#include <string>
#include <vector>
#include <fstream>

class Level
{
    public:
        //Initialize the level
        Level(int levelNum);

        void loadTileset(SDL_Renderer* renderer, std::string path, int columns, int rows);

        //Render all the tiles
        void Render(SDL_Rect camera);

        //Returns all the collider objects on the map
        std::vector<SDL_Rect> getColliders();

    private:
        Tileset mTileset;
        std::vector<Tile> mTilemap;
        std::vector<SDL_Rect> mColliders;
};