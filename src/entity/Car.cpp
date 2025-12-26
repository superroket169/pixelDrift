#include "Car.h"

void Car::update(const KeyInput& keyInput, const Track& track, float dt)
{
    Physics::PhysicsInput physicsInput;
    Physics::PhysicsOutput physicsOutput;

    // bools:
    physicsInput.autoGear = KeyInput::isDown(Action::GearAuto);
    physicsInput.brake = KeyInput::isDown(Action::Brake);
    physicsInput.handbrake = KeyInput::isDown(Action::HandBrake);
    physicsInput.throttle = KeyInput::isDown(Action::Throttle);

    physicsInput.carAngle = rotation;
    physicsInput.gear = gear;
    physicsInput.steerDir;
    physicsInput.steeredTime;
    physicsInput.velocityX;
    physicsInput.velocityY;

    if(KeyInput::isDown(Action::GearAuto))
    {
        
    }
    else if(KeyInput::isDown(Action::GearDown))
    {
        
    }
    else if(KeyInput::isDown(Action::GearUp))
    {
        
    }
    else if(KeyInput::isDown(Action::HandBrake))
    {
        
    }
    else if(KeyInput::isDown(Action::Pause))
    {
        
    }
    else if(KeyInput::isDown(Action::SteerLeft))
    {
        
    }
    else if(KeyInput::isDown(Action::SteerRight))
    {
        
    }
    else if(KeyInput::isDown(Action::Throttle))
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


