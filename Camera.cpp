#include "Camera.hpp"
#include "Settings.hpp"

Camera::Camera(Vector3& position, Vector3& direction, Settings& settings)
{
	auto theta = degreesToRadians(settings.fov);
	auto h = tan(theta / 2);
	auto viewport_height = 2.0 * h;
	auto viewport_width = settings.aspectRatio * viewport_height;

	w = Vector3(position - direction).normalize();
	u = Vector3(Vector3::cross({ 0, 1, 0 }, w)).normalize();
	v = Vector3::cross(w, u);

	origin = position;
	horizontal = settings.focusDist * viewport_width * u;
	vertical = settings.focusDist * viewport_height * v;
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - settings.focusDist * w;

	lens_radius = settings.aperture / 2;
}
