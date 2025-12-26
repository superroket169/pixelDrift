#pragma once

#include "../core/Coord.h"
#include "../input/Input.h"
#include "../physics/CarPhysics.h"
#include "../world/Track.h"
#include <cstdint>

class Car
{
public:
    Car() = default;

    void update(const KeyInput& input, const Track& track, float dt);

    Coord getPosition() const;
    float getRotation() const;
    float getSpeed() const;
    float getRPM() const;

private:
    Coord position;
    float rotation = 0.f;
    float speed = 0.f;
    float rpm = 0.f;

    Physics::PhysicsOutput physicsOut;

    float throttle = 0.f;
    float brake = 0.f;
    float handBrake = 0.f;
    float steer = 0.f;
    Physics::Gear gear = Physics::Gear::One;

    void applyPhysicsPhysicsOutput(float dt);
};
