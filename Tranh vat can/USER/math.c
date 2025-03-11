#include "math.h"

// abs
float abs(float number)
{
	return (number >= 0) ? number : -number;
}
// min
float min(float a, float b)
{
	return a<b ? a : b;
}
// max
float max(float a, float b)
{
	return a>b ? a : b;
}

