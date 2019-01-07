#pragma once

#include <SDL.h>

class Tile
{
    public:
        Tile(int index, SDL_Rect position, bool collides);
        int getIndex();
        SDL_Rect getPos();
        bool isCollider();

    private:
        int mIndex;
        SDL_Rect mPosition;
        bool mCollides;
};