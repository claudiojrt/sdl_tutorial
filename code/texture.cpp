#include "texture.hpp"

Texture::Texture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mAngle = 0;
	mCenter = NULL;
	mFlipMode = SDL_FLIP_NONE;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

	mRenderer = renderer;

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mAngle = 0;
		mCenter = NULL;
		mFlipMode = SDL_FLIP_NONE;
	}
}

void Texture::render(int x, int y, SDL_Rect clip, SDL_Rect camera, double scale)
{
	//Set rendering space and render to screen
	SDL_Rect space = {x - camera.x, y - camera.y, scale*clip.w, scale*clip.h};

	//Renderer, the texture itself, the portion of the image to render, the position on the screen, angle/center/flip.
	SDL_RenderCopyEx(mRenderer, mTexture, &clip, &space, mAngle, mCenter, mFlipMode);
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

void Texture::setRotationAngle(double angle)
{
	mAngle = angle;
}

void Texture::setCenter(SDL_Point* center)
{
	mCenter = center;
}

void Texture::setFlipMode(SDL_RendererFlip mode)
{
	mFlipMode = mode;
}