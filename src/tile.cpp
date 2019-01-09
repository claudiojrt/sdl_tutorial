#include <tile.hpp>

Tile::Tile(int index, SDL_Rect position, bool collides)
{
    mIndex = index;
    mPosition = position;
    mCollides = collides;
}

int Tile::getIndex()
{
    return mIndex;
}

SDL_Rect Tile::getPos()
{
    return mPosition;
}

bool Tile::isCollider()
{
    return mCollides;
}