#include "Utils.h"

float sigmoid(float x, float mid, float y1, float y2, float k)
{
    return y1 + (y2 - y1) / (1.0f + expf(-k * (x - mid)));
}

// have no idea about what ı should do here too