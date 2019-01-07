#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "timer.h"

Texture::Texture()
{
	mFrames = 0;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mCounter = 0;
	mAnimationSpeedVSync = 0;
	mAngle = 0;
	mCenter = NULL;
	mFlipMode = SDL_FLIP_NONE;
	mTimer.stop();
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path, int frames, int animationSpeedVSync)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    //Get image dimensions
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

	mFrames = frames;
	mAnimationSpeedVSync = animationSpeedVSync;


	int fW = mWidth / mFrames;
	for(int i = 1; i <= mFrames; i++) 
	{
		mSpriteClips.push_back({i * fW - fW, 0 ,fW , mHeight});
	}

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
		mFrames = 0;
		mCounter = 0;
		mAnimationSpeedVSync = 0;
		mAngle = 0;
		mCenter = NULL;
		mFlipMode = SDL_FLIP_NONE;
		mTimer.stop();
	}
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int frame)
{
	//Set rendering space and render to screen
	SDL_Rect space = {x, y, mWidth/mFrames, mHeight};
	SDL_Rect clip = mSpriteClips[frame];
	SDL_RenderCopyEx(renderer, mTexture, &mSpriteClips[frame], &space, mAngle, mCenter, mFlipMode);
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

int Texture::getFrames()
{
	return mFrames;
}

int Texture::getAnimationSpeed()
{
	return mAnimationSpeedVSync;
}

double Texture::getRotationAngle()
{
	return mAngle;
}

SDL_Point* Texture::getCenter()
{
	return mCenter;
}

SDL_RendererFlip Texture::getFlipMode()
{
	return mFlipMode;
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