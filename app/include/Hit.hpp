#pragma once

#include "Math.hpp"
#include <vector>

class Tri;

struct Hit {
	double t = infinity;

	Vector3 point;
	Vector3 color;

	std::vector<Tri*> triangles;
};
