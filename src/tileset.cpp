#include <tileset.hpp>

Tileset::Tileset()
{
    mRenderer = NULL;
    mTexture.free();
    mTiles.clear();
}

Tileset::~Tileset()
{
    mRenderer = NULL;
    mTexture.free();
    mTiles.clear();
}

void Tileset::loadFromFile(SDL_Renderer* renderer, std::string path, int columns, int rows)
{
    mTexture.loadFromFile(renderer, path.c_str());

    int w = mTexture.getWidth() / columns;
    int h = mTexture.getHeight() / rows;
    int x = 0;
    int y = 0;

    for(int row = 1; row <= rows; row++)
    {
        for(int column = 1; column <= columns; column++)
        {
            x = column * w - w;
            y = row * h - h;

            mTiles.push_back({x, y, w , h});
        }
    }

    mRenderer = renderer;
}

void Tileset::render(SDL_Rect camera, int tile, SDL_Rect pos)
{
    mTexture.render(pos.x, pos.y, mTiles[tile], camera, 1);
}