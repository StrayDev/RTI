#pragma once

#include "Math.hpp"
#include "Physics.hpp"

struct Settings;

class Camera
{
public:
	explicit Camera(Vector3& position, Vector3& direction, Settings& settings);

private:
	Vector3 origin{};
	Vector3 lower_left_corner{};
	Vector3 horizontal{};
	Vector3 vertical{};
	Vector3 u{}, v{}, w{};
	double lens_radius;
};
