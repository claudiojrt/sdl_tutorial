#include "player.hpp"

Player::Player()
{
    mDirX = 0;
    mDirY = 0;
	mPosX = 0;
    mPosY = 0;
	mVelX = 0;
    mVelY = 0;
    mAcelX = 12;
    mAcelY = -20;
    mJumping = false;
    mFalling = false;
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
                    moveLeft();
                }
                else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
                {
                    moveRight();
                }
                else
                {
                    stopMove();
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
    else if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_SPACE:
                startJump();
                break;
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

    //Moves in Y axis
    mPosY += mVelY;
    for(SDL_Rect o : objects)
    {
        if(isCollidingWith(o))
        {
            mJumping = false; //Identify when the player touches the ground to clean it
            mPosY -= mVelY;
            mVelY = 0;
        }
    }

    //Limits of the map
    if(mPosX < 0 || (mPosX + idle.getWidth() > LEVEL_WIDTH))
    {
        mPosX -= mVelX;
    }
    if(mPosY >= LEVEL_HEIGHT - idle.getHeight())
    {
        mPosY = LEVEL_HEIGHT - idle.getHeight();
        mJumping = false;
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

void Player::render(SDL_Rect camera)
{
    //Blink
    idle.setColor(idle.mTimer.getTicks() / 4, idle.mTimer.getTicks() / 4, idle.mTimer.getTicks() / 4);

    if(mJumping)
    {
        jump.render(mPosX, mPosY, camera);
    }
    else
    {
        idle.render(mPosX, mPosY, camera);
    }
}

//Return true if the instance is colliding with the object
bool Player::isCollidingWith(SDL_Rect& object)
{
    int aX1, aX2;
    int aY1, aY2;
    int bX1, bX2;
    int bY1, bY2;

    aX1 = mPosX;
    aX2 = mPosX + idle.getWidth();
    aY1 = mPosY;
    aY2 = mPosY + idle.getHeight();

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
            //If overlaping on both axis, a colision happened
            return true;
        }
    }
    
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

void Player::moveLeft()
{
    idle.setFlipMode(SDL_FLIP_HORIZONTAL);
    jump.setFlipMode(SDL_FLIP_HORIZONTAL);
    mDirX = -1;
    mVelX = -mAcelX;
}

void Player::moveRight()
{
    idle.setFlipMode(SDL_FLIP_NONE);
    jump.setFlipMode(SDL_FLIP_NONE);
    mDirX = 1;
    mVelX = mAcelX;
}

void Player::stopMove()
{
    //Stays in the current flip mode
    mDirX = 0;
    mVelX = 0;
}

void Player::startJump()
{
    if(!mJumping)
    {
        mJumping = true;
        mVelY = mAcelY;
    }
}