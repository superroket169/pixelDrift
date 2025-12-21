#pragma once

enum class Action
{
    Throttle,
    Brake,
    HandBrake,
    Pause,
    SteerRight,
    SteerLeft,
    GearAuto,
    GearUp,
    GearDown
};

class Input 
{
public:
    static void update();
    static bool isDown(Action action);
    static bool isPressed(Action action);
};
