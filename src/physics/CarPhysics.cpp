// CarPhysics.cpp:
#include "CarPhysics.h"
#include "../core/Utils.h"
#include "../core/Config.h"

Physics::Output Physics::CarPhysics::update(const Input& input, float dt)
{
    Physics::Output out;

    out.acceleration = computeAcceleration(input.speed, input.gear, input.throttle);
    out.angularVelocity = computeSteer(input.speed, input.steeredTime ,input.steerDir);
    out.slip = input.handbrake;

    if(input.autoGear)
        out.recommendedGear = calculateOptGear(input.speed);
    else
        out.recommendedGear = input.gear;

    return out;
}

Physics::Gear Physics::CarPhysics::calculateOptGear(float speed) const
{
    
    for(size_t i = 1; i <= 7; ++i)
        if(speed < gearMaxes[i] * recommenedGearConstant) return static_cast<Physics::Gear>(i);

    return Physics::Gear::Seven;
}

float Physics::CarPhysics::computeAcceleration(float speed, Physics::Gear gear, bool throttle) const
{
    if(throttle)
    {
        if(gear == Physics::Gear::R) return gearAccels[0];
        int intGear = static_cast<int>(gear);
        return sigmoid(speed, gearMaxes[intGear] / 3, gearMaxes[1] * gearMaxes[1] / gearMaxes[intGear], gearAccels[intGear], SigmoidKConstant);

        // plan : sigmoid will be simplefied
    }
    return 0;
}

float Physics::CarPhysics::computeSteer(float speed, float steeredTime, steerStatus steerDir) const
{
    if(steerDir == Physics::steerStatus::Left) return -turnSpeed * pow(speed, turnPowConstant) * steeredTime;
    if(steerDir == Physics::steerStatus::Right) return turnSpeed * pow(speed, turnPowConstant) * steeredTime;
    return 0.f;
}
