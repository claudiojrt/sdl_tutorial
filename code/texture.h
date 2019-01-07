#pragma once

#include <string>
#include <SDL.h>

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
		void render(SDL_Renderer* renderer, int x, int y);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:

		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};