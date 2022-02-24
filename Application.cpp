#include "Application.hpp"
#include "Tri.hpp"
#include "Vector3.hpp"

std::unique_ptr<Application> Application::Create()
{
	struct App : Application {};
	return std::make_unique<App>();
}

void Application::run()
{
	auto tri = Tri{ Vector3{ -1, -1, 0 }, { 1, -1, 0 }, { 0, 1, 0 } };
	auto n = GetNormal(tri);
	std::cout << n;

	/// does the ray intersect the plane the triangle is aligned with

	/// if true : does the point of intersection lie inside the triangle
}
