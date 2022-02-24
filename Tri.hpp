#pragma once

#include <array>

#include "Vector3.hpp"

using Tri = std::array<Vector3, 3>;

inline Vector3 GetNormal(const Tri& tri)
{
	/// get the vectors from point 0 to point 1 and 2
	auto a = tri[1] - tri[0];
	auto b = tri[2] - tri[0];

	/// the cross product is the triangles normal
	auto c = Vector3::cross(a, b);

	/// convert to a unit vector and return
	return c.normalize();
}
