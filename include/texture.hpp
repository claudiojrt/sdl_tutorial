#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <timer.hpp>
#include <iostream>
#include <string>
#include <vector>

class Texture
{
    public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile(SDL_Renderer* renderer, std::string path);

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render(int x, int y, SDL_Rect clip, SDL_Rect camera, double scale);

		//Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Get size
		int getWidth();
		int getHeight();

		//Setters
		void setRotationAngle(double angle);
		void setCenter(SDL_Point* center);
		void setFlipMode(SDL_RendererFlip mode);

	private:
		//Renderer
		SDL_Renderer* mRenderer;

		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;

		double mAngle;
		SDL_Point* mCenter;
		SDL_RendererFlip mFlipMode;
};