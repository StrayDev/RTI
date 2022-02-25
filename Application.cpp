#include "Application.hpp"
#include "Math.hpp"
#include "Physics.hpp"
#include "Tri.hpp"
#include "Vector3.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

std::unique_ptr<Application> Application::Create()
{
	struct App : Application {
	};
	return std::make_unique<App>();
}

void Application::run()
{
	/// settings
	const auto width = 640;
	const auto height = 480;

	double fov = 90;
	double scale = tan(degreesToRadians(fov * 0.5f));
	double aspectRatio = width / static_cast<double>(height);

	/// scene
	auto tri = Tri();
	tri[0] = { 0, 0, -1 };
	tri[1] = { .5, 0, -1 };
	tri[2] = { .25, .5, -1 };

	/// ray // this will change to camera
	auto origin = Vector3{ 0, 0, 0 };

	// TODO : TEMP
	std::cout << "P3\n"
			  << width << " " << height << "\n255\n";

	/// render : for each pixel
	for (auto j = 0; j < height; ++j)
	{
		for (auto i = 0; i < width; ++i)
		{
			/// get ray direction
			auto x = (2 * (i + 0.5) / double(width - 1)) * aspectRatio * scale;
			auto y = (1 - 2 * (j + 0.5) / double(height)) * scale;

			auto direction = Vector3{ x, y, -1 };
			direction = direction.normalize();

			/// if the ray intersects the triangle
			auto ray = Physics::Ray(origin, direction);
			auto hit = Physics::Hit();

			if (Physics::raycast(ray, hit, tri))
			{
				std::cout << 255 << ' ' << 255 << ' ' << 255 << '\n';
			}
			else
			{
				auto r = double(j) / (width - 1);
				auto g = double(i) / (height - 1);
				auto b = 0.25;

				int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);

				std::cout << ir << ' ' << ig << ' ' << ib << '\n';
			}
		}
	}
}
