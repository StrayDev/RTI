#pragma once

#include <cmath>
#include <random>

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

static double RandomDouble()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

