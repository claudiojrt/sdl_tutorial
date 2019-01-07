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

		//Gets image dimensions
		int getWidth();
		int getHeight();
		int getFrames();
		int getAnimationSpeed();

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
};