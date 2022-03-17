#include "Application.hpp"
#include "AABB.hpp"
#include "BVHNode.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "ObjLoader.hpp"
#include "Ray.hpp"
#include "Settings.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>

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
	/// start timer
	auto start = std::chrono::high_resolution_clock::now();

	/// create the camera
	auto camera = Camera(Vector3{ 0, 1, 1 }, Vector3{ 0, 0, 1 }); /// direction not in yet

	/// testing import of tiny obj
	auto objloader = ObjLoader();
	objloader.LoadObj("bunny.obj", "bunny");
	auto bunny_1 = objloader.CreateObject("bunny", {0, 0,0 });
	auto triList = bunny_1->triangles;

	std::cout << triList[0].GetVertices()[0] << '\n';

	/// render methods
	//RenderBasic(triList, camera);
	RenderBVH(camera, triList);

	/// stop the timer and print result
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << '\n' << "Write time : " << duration.count()/1000.f << '\n';
}

void Application::RenderBVH(const Camera& camera, const std::vector<Tri>& triList)
{
	/// build the BVH
	auto root_node = BVHNode(triList);

	/// Create file
	auto file = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
	file << "P3\n" << screen_width << " " << screen_height << "\n255\n";

	/// render : for each pixel
	for (int j = screen_height; j > -1; --j)
	{
		std::cerr << "\r Lines remaining : " << std::setfill('0') << std::setw(4) << j << std::flush;

		for (auto i = 0; i < screen_width; ++i)
		{
			/// get ray direction
			auto u = static_cast<double>(i) / (screen_width - 1);
			auto v = static_cast<double>(j) / (screen_height - 1);

			/// if the ray intersects the triangle
			auto ray = Ray(camera.position, camera.GetDirectionFromUV(u, v));
			auto hit = Hit();

			/// navigate bvh
			root_node.hit(ray, hit);

			if (hit.t < infinity)
			{
				/// colour from normals
				int ir = static_cast<int>(255.999 * hit.color.x());
				int ig = static_cast<int>(255.999 * hit.color.y());
				int ib = static_cast<int>(255.999 * hit.color.z());

				if (hit.color.x() != hit.color.x() || hit.color.y() != hit.color.y() || hit.color.z() != hit.color.z())
				{
					std::cout << "NaN\n";
				}

				file << ir << ' ' << ig << ' ' << ib << '\n';

				continue;
			}

			DrawBackground(file, i, j);
		}
	}
	file.close();
}

void Application::RenderBasic(const std::vector<Tri>& tri_list, const Camera& camera)
{
	/// Create file
	auto file = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
	file << "P3\n"
		 << screen_width << " " << screen_height << "\n255\n";

	/// Create outer bounding box // TODO : should this be done during mesh creation?
	AABB bounding_box{};
	AABB triBoundingBox{};

	/// this will be removed
	for (auto tri : tri_list)
	{
		bounding_box = AABB::MergeBounds(bounding_box, tri.GetAABB());
	}

	/// render : for each pixel
	for (int j = static_cast<int>(screen_height); j > -1; --j)
	{
		std::cerr << "\rLines remaining : " << j << std::flush;

		for (int i = 0; i < screen_width; ++i)
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
				DrawBackground(file, i, j);
				continue;
			}

			/// foreach tri check intersect and update hit
			for (auto tri : tri_list)
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
				/*				if (hit.color.x() != hit.color.x() || hit.color.y() != hit.color.y() || hit.color.z() != hit.color.z())
				{
				}*/
				file << ir << ' ' << ig << ' ' << ib << '\n';
				//file << 50 << ' ' << 10 << ' ' << 10 << '\n';
			}
			else
			{
				DrawBackground(file, i, j);
				/// visualise the base bounding box
				//file << 50 << ' ' << 50 << ' ' << 50 << '\n';
			}
		}
	}
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
