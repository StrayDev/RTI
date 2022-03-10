#pragma once

#include "Ray.hpp"
#include "Vector3.hpp"

class AABB
{
public:
	AABB() = default;
	AABB(const Vector3& a, const Vector3& b)
	{
		minimum = a;
		maximum = b;
		centre = maximum - minimum;
	}

	[[nodiscard]] Vector3 mid() const { return centre; }
	[[nodiscard]] Vector3 min() const { return minimum; }
	[[nodiscard]] Vector3 max() const { return maximum; }

	[[nodiscard]] bool hit(const Ray& r, double t_min, double t_max) const;

public:
	static AABB MergeBounds(AABB box1, AABB box2);

	Vector3 centre;
	Vector3 minimum;
	Vector3 maximum;
};
