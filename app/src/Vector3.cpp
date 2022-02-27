#include "Vector3.hpp"
#include <cmath>

double Vector3::length() const
{
	return sqrt(lengthSquared());
}

double Vector3::lengthSquared() const
{
	return x() * x() + y() * y() + z() * z();
}

Vector3 Vector3::normalize() const
{
	return *this / length();
}
