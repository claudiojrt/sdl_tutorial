#include "player.h"
#include "global.h"
#include <cmath>

Player::Player()
{
    mDirX = 0;
    mDirY = 0;
	mPosX = 0;
    mPosY = 0;
	mVelX = 0;
    mVelY = 0;
    mAcelX = 7;
    mAcelY = -15;
    mJumping = false;
}

void Player::handleEvent(SDL_Event& event)
{
    if(event.type == SDL_JOYAXISMOTION)
    {
        if(event.jaxis.which == 0)
        {
            // X axis
            if(event.jaxis.axis == 0)
            {
                if(event.jaxis.value < -JOYSTICK_DEAD_ZONE)
                {
                    sprite.setFlipMode(SDL_FLIP_HORIZONTAL);
                    jump.setFlipMode(SDL_FLIP_HORIZONTAL);
                    mDirX = -1;
                    mVelX = -mAcelX;
                }
                else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
                {
                    sprite.setFlipMode(SDL_FLIP_NONE);
                    jump.setFlipMode(SDL_FLIP_NONE);
                    mDirX = 1;
                    mVelX = mAcelX;
                }
                else
                {
                    mDirX = 0;
                    mVelX = 0;
                }   
            }
        }
    }
    if(event.type == SDL_JOYBUTTONDOWN)
    {
        switch(event.jbutton.button)
        {
            case 0:
                if(!mJumping)
                {
                    mJumping = true;
                    mVelY = mAcelY;
                    break;
                }
        }
    }
}

void Player::move(std::vector<SDL_Rect> objects)
{
    //Moves in X axis
    mPosX += mVelX;
    for(SDL_Rect o : objects)
    {
        if(isCollidingWith(o))
        {
            mPosX -= mVelX;
            continue;
        }
    }
    if(mPosX < 0 || (mPosX + sprite.getWidth() > LEVEL_WIDTH))
    {
        mPosX -= mVelX;
    }

    //Moves in Y axis
    mPosY += mVelY;
    for(SDL_Rect o : objects)
    {
        if(isCollidingWith(o))
        {
            mPosY -= mVelY;
            mVelY = 0;
        }
    }
    if(mPosY >= LEVEL_HEIGHT - sprite.getHeight())
    {
        mPosY = LEVEL_HEIGHT - sprite.getHeight();
        mVelY = 0;
    }

    //Gravity
    //ALWAYS REMEMBER: WHEN COLLIDING IN Y AXIS, MUST CLEAN THE Y VELOCITY
    mVelY += FALL_VELOCITY;
    if(mVelY > 20)
        mVelY = 20;
}

void Player::setPos(int x, int y)
{
    mPosX = x;
    mPosY = y;
}

void Player::render(SDL_Renderer* renderer, SDL_Rect camera)
{
    //Blink

    sprite.setColor(sprite.mTimer.getTicks() / 4, sprite.mTimer.getTicks() / 4, sprite.mTimer.getTicks() / 4);

    if(mJumping)
    {
        //When the next counter++ == the max counter number
        if(jump.mCounter + 1 == jump.getAnimationSpeed() * jump.getFrames())
            mJumping = false;

        jump.render(renderer, mPosX, mPosY, jump.mCounter / jump.getAnimationSpeed(), camera, 1);
    }
    else
    {
        sprite.render(renderer, mPosX, mPosY, sprite.mCounter / sprite.getAnimationSpeed(), camera, 1);
    }
}

//Return true if the instance is colliding with the parameter object
bool Player::isCollidingWith(SDL_Rect& object)
{
    //return SDL_IntersectRect(&object, &mCollider, NULL);

    int aX1, aX2;
    int aY1, aY2;
    int bX1, bX2;
    int bY1, bY2;

    aX1 = mPosX;
    aX2 = mPosX + sprite.getWidth();
    aY1 = mPosY;
    aY2 = mPosY + sprite.getHeight();

    bX1 = object.x;
    bX2 = object.x + object.w;
    bY1 = object.y;
    bY2 = object.y + object.h;

    // ax1             ax2
    //  |---------------|
    //            |--------------|
    //           bx1            bx2

    //Overlaping on x axis
    if(aX1 <= bX2 && bX1 <= aX2)
    {
        //Overlaping on y axis
        if(aY1 <= bY2 && bY1 <= aY2)
        {
            return true;
        }
    }
    
    //If overlaping on both axis, a colision happened
    return false;
}

int Player::getPosX()
{
    return mPosX;
}

int Player::getPosY()
{
    return mPosY;
}