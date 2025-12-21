#pragma once

/*
    what will happen here:
        Optimum gear calculate for autoGear
        steerign code for steering 
        acceleration code with sigmoids

    planed : bool  rearSlip;
    planed : float slipAmount;
        
*/

namespace Physics
{

    enum class Gear
    {
        R = 0,
        One = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7
    };

    enum class steerStatus
    {
        Left = -1,
        Right = 1,
        Forward = 0
    };

    struct Input
    {
        float speed;
        float steeredTime;
        steerStatus steerDir;
        bool throttle;     // aralık :  0 -> 1
        bool  handbrake;
        bool  brake;
        Gear  gear;
        bool  autoGear;
    };

    struct Output
    {
        float acceleration;
        float angularVelocity;
        bool  slip;
        // planed : bool  rearSlip;
        // planed : float slipAmount;
        Gear  recommendedGear;
    };

    class CarPhysics
    {
    public:
        Output update(const Input& input, float dt);

    private:
        Gear calculateOptGear(float speed) const;
        float computeAcceleration(float speed, Gear gear, bool throttle) const;
        float computeSteer(float speed, float steeredTime, steerStatus steerDir) const;
    };
}

// brake kodu eklenecek
