#include "Car.h"

void Car::update(const Input& input, const Track& track, float dt)
{
    if(Input::isDown(Action::Brake))
    {
        
    }
    else if(Input::isDown(Action::GearAuto))
    {
        
    }
    else if(Input::isDown(Action::GearDown))
    {
        
    }
    else if(Input::isDown(Action::GearUp))
    {
        
    }
    else if(Input::isDown(Action::HandBrake))
    {
        
    }
    else if(Input::isDown(Action::Pause))
    {
        
    }
    else if(Input::isDown(Action::SteerLeft))
    {
        
    }
    else if(Input::isDown(Action::SteerRight))
    {
        
    }
    else if(Input::isDown(Action::Throttle))
    {
        
    }

    return;
}

Coord Car::getPosition() const
{
    return position;
}

float Car::getRotation() const
{
    return rotation;
}

float Car::getSpeed() const
{
    return speed;
}

float Car::getRPM() const
{
    return rpm;
}


