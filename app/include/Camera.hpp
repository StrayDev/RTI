#pragma once

#include "Math.hpp"
#include "Vector3.hpp"

struct Settings;

class Camera
{
public:
	Camera(const Vector3& pos, const Vector3& dir) : position(pos), direction(dir) {}
	~Camera() = default;

	Vector3 GetDirectionFromUV(double u, double v) const { return lower_left_corner + u * horizontal + v * vertical - position; }

	const Vector3 position;
	const Vector3 direction; // not currently used

	const double viewport_height = 2.f;
	const double viewport_width = (16.f / 9.f) * viewport_height;
	const double focal_length = 1.f;
	const double fov = 60.f;

	const Vector3 horizontal = Vector3(viewport_width, 0, 0);
	const Vector3 vertical = Vector3(0, viewport_height, 0);
	const Vector3 lower_left_corner = position - horizontal / 2 - vertical / 2 - Vector3(0, 0, focal_length);
};
