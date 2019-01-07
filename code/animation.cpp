#include "animation.hpp"

void Animation::loadFromFile(SDL_Renderer* renderer, std::string path, int frames, int animationSpeedVSync)
{
    mAnimationSpeedVSync = animationSpeedVSync;
    mFrames = frames;
    mSpritesheet.loadFromFile(renderer, path.c_str());

    mWidth = mSpritesheet.getWidth() / mFrames;
	mHeight = mSpritesheet.getHeight();

	for(int i = 1; i <= mFrames; i++) 
	{
		mSpriteClips.push_back({i * mWidth - mWidth, 0 ,mWidth , mHeight});
	}
}

void Animation::render(int x, int y, SDL_Rect camera)
{
    mSpritesheet.render(x, y, mSpriteClips[mCounter/mAnimationSpeedVSync], camera, 1);

    //Each time it renders, it calculates via animation speed what frame will be the next
	if(mAnimationSpeedVSync > 0)
	{
		mCounter++;
    	if(mCounter / mAnimationSpeedVSync >= mFrames)
        	mCounter = 0;
	}
}

void Animation::setColor(int r, int g, int b)
{
    mSpritesheet.setColor(r, g, b);
}

void Animation::setRotationAngle(double angle)
{
	mSpritesheet.setRotationAngle(angle);
}

void Animation::setCenter(SDL_Point* center)
{
	mSpritesheet.setCenter(center);
}

void Animation::setFlipMode(SDL_RendererFlip mode)
{
	mSpritesheet.setFlipMode(mode);
}

int Animation::getWidth()
{
	return mWidth;
}

int Animation::getHeight()
{
	return mHeight;
}