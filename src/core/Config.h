#pragma once

#include<cstdint>
#include<string>

#define PI 3.14159265358979323846f

inline constexpr uint8_t WINDOW_WIDTH =     1200;
inline constexpr uint8_t WINDOW_HEIGHT =    1200;

//sınır algılaması:
inline constexpr float MIN_X =             -5400.f;
inline constexpr float MAX_X =              600.f;
inline constexpr float MIN_Y =             -5600.f;
inline constexpr float MAX_Y =              410.f;

inline constexpr char fontPath[] =          "../assets/fonts/DejaVuSans-Bold.ttf";
inline constexpr char carAssetPath[] =      "../assets/cars/default/DefaultCarTexture.png";
inline constexpr char backGroundPath[] =    "../assets/maps/default/backGround2.png";

inline constexpr float damping = 0.5;

inline constexpr float gearAccels[8] = {
    -500 * damping,
    300  * damping,
    700  * damping,
    1200 * damping,
    1800 * damping,
    2300 * damping,
    2650 * damping,
    2900 * damping
};

inline constexpr float gearMaxes[8] = {
    125, 
    300, 
    700, 
    1200, 
    1800, 
    2300, 
    2650, 
    2900
};

inline constexpr float recommenedGearConstant = 0.75f;

inline constexpr float gearRtrMaxVel_kmh =  14;
inline constexpr float gearOneMaxVel_kmh =  35;
inline constexpr float gearSecMaxVel_kmh =  85;
inline constexpr float gearThiMaxVel_kmh =  143;
inline constexpr float gearFrtMaxVel_kmh =  215;
inline constexpr float gearFthMaxVel_kmh =  275;
inline constexpr float gearSixMaxVel_kmh =  320;
inline constexpr float gearSvnMaxVel_kmh =  350;

inline constexpr float Sigm =               0.012;

inline constexpr float brakeForce =         2.2;
inline constexpr float handBrakeForce =     0.3;

inline constexpr float turnSpeed =          0.001;
inline constexpr float maxTurnSpeed =       150;
inline constexpr float maxRPM =             7000;

inline constexpr float DEG2RAD =            PI / 180;
inline constexpr float RAD2DEG =            180 / PI;

inline constexpr uint32_t maxLifeMarkSec =  7;