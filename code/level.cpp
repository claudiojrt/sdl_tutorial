#include "level.hpp"

Level::Level(int levelNum)
{
    std::vector<int> level = {
        0,0,0,0,1,1,1,0,0,0,2,2,2,0,0,3,3,3,0,0
    };

    int x = 0;
    int y = 0;
    bool collides;

    for(int i = 0; i < level.size(); i++)
    {
        x = i * TILE_SIZE;
        y = LEVEL_HEIGHT - TILE_SIZE - TILE_SIZE - TILE_SIZE;

        if(level[i] > 0)
            collides = true;
        else
            collides = false;
        
        Tile newTile(level[i], {x, y, TILE_SIZE, TILE_SIZE}, collides);
        mTilemap.push_back(newTile);
    }

    for(int i = 0; i < mTilemap.size(); i++)
    {
        if(mTilemap[i].isCollider())
        {
            mColliders.push_back(mTilemap[i].getPos());
        }
    }

    /* std::string line;
    std::ifstream infile("level/level1");

    std::vector<int> lines;

    while (std::getline(infile, line))
    {
        //Read space separated integers to create the thing
    } */
}

void Level::loadTileset(SDL_Renderer* renderer, std::string path, int columns, int rows)
{
    mTileset.loadFromFile(renderer, path.c_str(), columns, rows);
}

void Level::Render(SDL_Rect camera)
{
    for(int i = 0; i < mTilemap.size(); i++)
    {
        mTileset.render(camera, mTilemap[i].getIndex(), mTilemap[i].getPos());
    }
}

std::vector<SDL_Rect> Level::getColliders()
{
    return mColliders;
}