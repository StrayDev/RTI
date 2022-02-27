#include "Application.hpp"
#include "Math.hpp"
#include "Physics.hpp"
#include "Settings.hpp"

#include "ObjLoader.hpp"
#include <algorithm>
#include <fstream>

std::unique_ptr<Application> Application::Create()
{
	struct App : Application {
	};
	return std::make_unique<App>();
}

void Application::run()
{
	/// testing import of tiny obj
	auto objloader = ObjLoader();
	objloader.LoadObj("Cube.obj");
	auto triList = objloader.GetTriangleList();

	/// settings
	auto data = Settings{
		.screenWidth = 640,
		.screenHeight = 480,
		.cameraPosition = { 0, 0, 0 },
		.cameraDirection = { 0, 0, 1 },
		.fov = 40,
		.aspectRatio = 3.0 / 2.0,
		.aperture = 0.1,
		.focusDist = 10.0
	};

	//camera = std::make_unique<Camera>(data.cameraPosition, data.cameraDirection, data);

	auto scale = tan(degreesToRadians(data.fov * 0.5f));
	auto aspectRatio = data.screenWidth / static_cast<double>(data.screenHeight);

	/// scene
	auto tri = Tri();
	tri[0] = { 0, 0, -1 };
	tri[1] = { .5, 0, -1 };
	tri[2] = { .25, .5, -1 };

	/// ray // this will change to camera
	auto origin = data.cameraPosition;

	/// Create file
	auto file = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
	file << "P3\n"
		 << data.screenWidth << " " << data.screenHeight << "\n255\n";

	/// render : for each pixel
	for (auto j = 0; j < data.screenHeight; ++j)
	{
		std::cerr << "\rLines remaining : " << j << std::flush;

		for (auto i = 0; i < data.screenWidth; ++i)
		{
			/// get ray direction
			auto x = (2 * (i + 0.5) / double(data.screenWidth - 1)) * aspectRatio * scale;
			auto y = (1 - 2 * (j + 0.5) / double(data.screenHeight)) * scale;

			auto direction = Vector3{ x, y, -1 };
			direction = direction.normalize();

			/// if the ray intersects the triangle
			auto ray = Physics::Ray(origin, direction);
			auto hit = Physics::Hit();

			if (Physics::raycast(ray, hit, tri))
			{
				file << 255 << ' ' << 255 << ' ' << 255 << '\n';
			}
			else
			{
				auto r = double(j) / (data.screenWidth - 1);
				auto g = double(i) / (data.screenHeight - 1);
				auto b = 0.25;

				int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);

				file << ir << ' ' << ig << ' ' << ib << '\n';
			}
		}
	}
	std::cerr << '\n'
			  << "Write Complete" << '\n';
}
