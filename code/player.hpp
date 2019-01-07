#pragma once

#include <SDL.h>
#include "animation.hpp"
#include "helper.hpp"
#include <cmath>

class Player
{
    public:
		Player();

		//Events
		void handleEvent(SDL_Event& event);
		void move(std::vector<SDL_Rect> objects);
		void render(SDL_Rect camera);

		//Positional
        void setPos(int x, int y);
		int getPosX();
		int getPosY();
		bool isCollidingWith(SDL_Rect& object);

		//Movement
		void moveLeft();
		void moveRight();
		void stopMove();
		void startJump();
		void stopJump();

		//Action animations
        Animation idle;
		Animation jump;

	private:
		int mAcelX, mAcelY;
		int mDirX, mDirY;
		int mPosX, mPosY;
		int mVelX, mVelY;

		bool mJumping;
		bool mFalling;
};