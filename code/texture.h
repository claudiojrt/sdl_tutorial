#pragma once

#include <string>
#include <SDL.h>
#include <vector>

class Texture
{
    public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile(SDL_Renderer* renderer, std::string path, int frames, int animationSpeedVSync);

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render(SDL_Renderer* renderer, int x, int y, int frame);

		//Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

		int getWidth();
		int getHeight();
		int getFrames();
		int getAnimationSpeed();
		double getRotationAngle();
		SDL_Point* getCenter();
		SDL_RendererFlip getFlipMode();

		void setRotationAngle(double angle);
		void setCenter(SDL_Point* center);
		void setFlipMode(SDL_RendererFlip mode);

		//Counter for the animations, public because yes
		int mCounter;

	private:

		//The actual hardware texture
		SDL_Texture* mTexture;

		//The sprite frames on the texture
		std::vector<SDL_Rect> mSpriteClips;

		//Image dimensions
		int mWidth;
		int mHeight;
		int mFrames;
		int mAnimationSpeedVSync;
		double mAngle;
		SDL_Point* mCenter;
		SDL_RendererFlip mFlipMode;
};