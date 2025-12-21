#pragma once
#include <chrono>

class Time
{
public:
    void start();
    void pause();
    void resume();
    float elapsedTime();

private:
    using Clock = std::chrono::high_resolution_clock;
    Clock::time_point lastTime;
    Clock::time_point startTime;
    Clock::time_point pausedTime;

    float delta = 0.0f;
    bool paused = false;
};