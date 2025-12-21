#include "Time.h"

void Time::start()
{
    lastTime = Clock::now();
    startTime = Clock::now();
    paused = false;
    delta = 0.0f;
}

void Time::pause()
{
    if(!paused)
    {
        pausedTime = Clock::now();
        paused = true;
    }
}

void Time::resume()
{
    if(paused)
    {
        auto now = Clock::now();
        lastTime += now - pausedTime;
        paused = false;
    }
}

float Time::elapsedTime()
{
    if(paused) 
        return std::chrono::duration<float>(pausedTime - startTime).count();
    else
        return std::chrono::duration<float>(Clock::now() - startTime).count();
}