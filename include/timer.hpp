#pragma once

#include <SDL.h>

class Timer
{
     public:
		Timer();

		void start();
		void stop();
		void pause();
		void unpause();

		bool isRunning();
		bool isPaused();

        Uint32 getTicks();

    private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
        
		bool mPaused;
		bool mRunning;
};