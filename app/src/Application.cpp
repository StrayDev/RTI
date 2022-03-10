#include "Application.hpp"
#include "AABB.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "ObjLoader.hpp"
#include "Ray.hpp"
#include "Settings.hpp"
#include "BVHNode.hpp"

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
	auto camera = Camera(Vector3{ 0, 1, 2 }, Vector3{ 0, 0, 0 });/// direction not in yet

	/// testing import of tiny obj
	auto objloader = ObjLoader();
	objloader.LoadObj("bunny.obj");
	auto triList = objloader.GetTriangleList();

	/// Create file
	auto file = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
	file << "P3\n"
		 << screen_width << " " << screen_height << "\n255\n";

	/// start timer
	auto start = std::chrono::high_resolution_clock::now();

	/// Create outer bounding box // TODO : should this be done during mesh creation?
	AABB bounding_box {};
	AABB triBoundingBox {};

	/// todo : build tree
	// build root node
	// split

	for (auto tri : triList)
	{
		bounding_box = AABB::MergeBounds(bounding_box, tri.GetBoundingBox());
	}

	auto root_node = BVHNode(triList);

	/// render : for each pixel
	for (int j = static_cast<int>(screen_height); j > -1 ; --j)
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

			/// check for ray aabb collision
			if (!bounding_box.hit(ray, 0, 999))
			{
				DrawBackground(file, i , j);
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
				/// colour from normals
				int ir = static_cast<int>(255.999 * hit.color.x());
				int ig = static_cast<int>(255.999 * hit.color.y());
				int ib = static_cast<int>(255.999 * hit.color.z());
				if (hit.color.x() != hit.color.x() || hit.color.y() != hit.color.y() || hit.color.z() != hit.color.z()){


				}
				file << ir << ' ' << ig << ' ' << ib << '\n';
				//file << 50 << ' ' << 10 << ' ' << 10 << '\n';
			}
			else
			{
				DrawBackground(file, i , j);
				/// visualise the base bounding box
				//file << 50 << ' ' << 50 << ' ' << 50 << '\n';
			}
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cerr << '\n'
			  << "Write time : " << duration << '\n';
}

void Application::DrawBackground(std::ofstream& file, int i, int j)
{
	auto r = double(j) / (screen_width - 1);
	auto g = double(i) / (screen_height - 1);
	auto b = 0.25;

	int ir = static_cast<int>(255.999 * r);
	int ig = static_cast<int>(255.999 * g);
	int ib = static_cast<int>(255.999 * b);

	file << ir << ' ' << ig << ' ' << ib << '\n';
}
