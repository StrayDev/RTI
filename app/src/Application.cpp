#include "Application.hpp"
#include "AABB.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "ObjLoader.hpp"
#include "Ray.hpp"
#include "Settings.hpp"

#include <chrono>
#include <fstream>

/// unique_ptr constructor replacement
std::unique_ptr<Application> Application::Create()
{
	struct App : Application {
	};
	return std::make_unique<App>();
}

/// init the app
void Application::init()
{
}

void Application::run()
{
	/// create the camera
	auto camera = Camera(Vector3{ 2, 2, 5 }, Vector3{ 0, 0, 0 });/// direction not in yet

	/// testing import of tiny obj
	auto objloader = ObjLoader();
	objloader.LoadObj("Cube.obj");
	auto triList = objloader.GetTriangleList();

	/// Create file
	auto file = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
	file << "P3\n"
		 << screen_width << " " << screen_height << "\n255\n";

	/// start timer
	auto start = std::chrono::high_resolution_clock::now();

	/// Create outer bounding box // TODO : create tree navigation
	AABB bounding_box{};
	AABB triBoundingBox{};

	for (auto tri : triList)
	{
		triBoundingBox = tri.getBoundingBox();
		bounding_box = AABB::MergeBounds(bounding_box, triBoundingBox);
	}

	std::cout << '\n'
			  << bounding_box.min() << " : " << bounding_box.max() << '\n';

	/// render : for each pixel
	for (auto j = 0; j < screen_height; ++j)
	{
		std::cerr << "\rLines remaining : " << j << std::flush;

		for (auto i = 0; i < screen_width; ++i)
		{
			/// get ray direction
			auto u = static_cast<double>(i) / (screen_width - 1);
			auto v = static_cast<double>(j) / (screen_height - 1);

			/// if the ray intersects the triangle
			auto ray = Ray(camera.position, camera.GetDirectionFromUV(u, v));
			auto hit = Hit();

			/// min and max length of the ray??? or not
			if (!bounding_box.hit(ray, 0, 999))
			{
				auto r = double(j) / (screen_width - 1);
				auto g = double(i) / (screen_height - 1);
				auto b = 0.25;

				int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);

				file << ir << ' ' << ig << ' ' << ib << '\n';
				continue;
			}

			/// foreach tri check intersect and update hit
			for (auto tri : triList)
			{
				tri.hit(ray, hit);
			}

			/// less than infinity means it hit
			if (hit.t < infinity)
			{
				int ir = static_cast<int>(255.999 * hit.color.x());
				int ig = static_cast<int>(255.999 * hit.color.y());
				int ib = static_cast<int>(255.999 * hit.color.z());

				file << ir << ' ' << ig << ' ' << ib << '\n';
			}
			else
			{
				auto r = double(j) / (screen_width - 1);
				auto g = double(i) / (screen_height - 1);
				auto b = 0.25;

				int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);

				file << ir << ' ' << ig << ' ' << ib << '\n';
			}
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cerr << '\n'
			  << "Write time : " << duration << '\n';
}
