#pragma once

#include "Vector3.hpp"

class Ray
{
public:
	Ray(const Vector3& origin, const Vector3& direction)
		: _origin(origin), _direction(direction) {}

	~Ray() = default;

public:
	[[nodiscard]] Vector3 getOrigin() const { return _origin; }
	[[nodiscard]] Vector3 getDirection() const { return _direction; }

private:
	Vector3 _origin{};
	Vector3 _direction{};
};
