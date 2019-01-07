#pragma once

#include <SDL.h>
#include "texture.h"

class Player
{
    public:
		Player();

		void handleEvent(SDL_Event& event);
		void move(std::vector<SDL_Rect> objects);
		void render(SDL_Renderer* renderer, SDL_Rect camera);
        void setPos(int x, int y);
		int getPosX();
		int getPosY();
		bool isCollidingWith(SDL_Rect& object);

        Texture sprite;
		Texture jump;

	private:
		int mAcelX, mAcelY;
		int mDirX, mDirY;
		int mPosX, mPosY;
		int mVelX, mVelY;

		bool mJumping;
};