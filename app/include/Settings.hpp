#pragma once

#include "Vector3.hpp"

struct Settings
{
	int screenWidth;
	int screenHeight;

	Vector3 cameraPosition;
	Vector3 cameraDirection;

	double fov;// in degrees
	double aspectRatio;
	double aperture;
	double focusDist;
};
