#pragma once

#include <cmath>

#include "Vector3.hpp"

static constexpr double pi = 3.14159265358979323846f;
static constexpr double epsilon = std::numeric_limits<double>::epsilon();
static constexpr double infinity = std::numeric_limits<double>::infinity();

static double degreesToRadians(double degrees)
{
	return ( degrees * pi ) / 180;
}

static double radiansToDegrees(double radians)
{
	return ( radians * 180 ) / pi;
}

