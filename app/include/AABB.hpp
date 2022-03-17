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
		mid = (a + b) / 2;
		extent = ( b - a ) / 2;
	}

	[[nodiscard]] Vector3 extents() const { return extent; }
	[[nodiscard]] Vector3 midpoint() const { return mid; }
	[[nodiscard]] Vector3 min() const { return minimum; }
	[[nodiscard]] Vector3 max() const { return maximum; }

	[[nodiscard]] Vector3 diagonal() const { return minimum - maximum; }

	[[nodiscard]] double surfaceArea() const
	{
		auto d = diagonal();
		return 2 * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
	}


	[[nodiscard]] bool hit(const Ray& r, double t_min, double t_max) const;

public:
	static AABB MergeBounds(AABB box1, AABB box2);

	Vector3 mid;
	Vector3 extent;
	Vector3 minimum;
	Vector3 maximum;
};
