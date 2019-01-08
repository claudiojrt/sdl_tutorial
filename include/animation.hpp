#pragma once

#include <SDL.h>
#include "../include/texture.hpp"
#include <vector>

class Animation
{
    public:
        void loadFromFile(SDL_Renderer* renderer, std::string path, int frames, int animationSpeedVSync);
        void render(int x, int y, SDL_Rect camera);
        void setColor(int r, int g, int b);
		void setRotationAngle(double angle);
		void setCenter(SDL_Point* center);
		void setFlipMode(SDL_RendererFlip mode);
        int getWidth();
        int getHeight();

        Timer mTimer;

    private:
        //The texture
        Texture mSpritesheet;
        int mWidth;
        int mHeight;

        //The size/position of the single frames on the sprite sheet
		std::vector<SDL_Rect> mSpriteClips;
        int mFrames;
        int mAnimationSpeedVSync;

        //Frame rendering counter, for the animations. Time of a sprite being rendered = counter(frames) / animation speed
        int mCounter;
};