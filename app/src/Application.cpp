#include "Application.hpp"
#include "AABB.hpp"
#include "BVHNode.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "ObjLoader.hpp"
#include "Ray.hpp"
#include "Settings.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <future>

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
	/// testing import of tiny obj
	auto objloader = ObjLoader();
	objloader.LoadObj("bunny.obj", "bunny");
	auto bunny_1 = objloader.CreateObject("bunny");

	//objloader.LoadObj("Cube.obj", "cube");
	//auto cube = objloader.CreateObject("cube");
	//auto cube2 = objloader.CreateObject("cube");
	//auto cube3 = objloader.CreateObject("cube");

	bunny_1->SetPosition({ .1, 0, 0 });
	//cube->SetPosition( { 0, -1.1, 0 });
	//cube2->SetPosition({1.999, -.5,.01});
	//cube3->SetPosition({-1.8, -.2,.001});

	/// create the camera
	auto camera = Camera(Vector3{ 0, 1, 2 }, Vector3{ 0, 0, 1 });  /// direction not in yet

	std::vector<Tri> triangle_list = bunny_1->triangles;
	//triangle_list.insert(triangle_list.end(), cube->triangles.begin(), cube->triangles.end());
	//triangle_list.insert(triangle_list.end(), cube2->triangles.begin(), cube2->triangles.end());
	//triangle_list.insert(triangle_list.end(), cube3->triangles.begin(), cube3->triangles.end());


	/// render methods
	//RenderBasic(triList, camera);
	//RenderBVH(camera, triangle_list);
	RenderBVHThreaded(camera, triangle_list);

	/// stop the timer and print result
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << "\n Write time      : " << duration.count() / 1000.f << '\n';
}

void Application::RenderBVHThreaded(const Camera& camera, const std::vector<Tri>& triList)
{
	/// build the BVH
	auto root_node = BVHNode(triList);

	/// create the buffer
	int channels = sizeof(unsigned char) * 3;
	auto buffer = std::unique_ptr<unsigned char[]>(new unsigned char[(screen_width * screen_height) * channels]);

	/// multithreading set up
	auto cores = std::thread::hardware_concurrency();
	std::vector<std::future<void>> future_vector;
	future_vector.reserve(cores);
	auto bucket = screen_height * screen_width / cores;

	/// todo : change this to segment into squares and reassign cores to them
	auto samples = 32;

	/// create the job
	auto job = [=, &root_node, &buffer](int start)
	{
		for (size_t index = start; index < start + bucket; index++)
		{
			int x = static_cast<int>(index % screen_width);
			int y = static_cast<int>(index / screen_width);

			/// always do at least 1 sample
			RenderPixel(x, y, samples, root_node, camera, buffer.get());
			for(auto s = samples; s > 1; --s)
			{
				RenderPixel(x, y, samples, root_node, camera, buffer.get());
			}
		}
	};

	/// loop through each available core
	for (size_t i = 0; i < cores; ++i)
	{
		auto start = bucket * i;
		future_vector.emplace_back(std::async(job, start));
	}

	/// wait for all the jobs to finish
	for(auto& f : future_vector)
	{
		f.wait();
	}

	/// write the png
	stbi_write_png("image.png", screen_width, screen_height, channels, buffer.get(), screen_width * channels);
}

void Application::RenderPixel(int i, int j, int samples, BVHNode& root, const Camera& camera, unsigned char* buffer)
{
	int channels = sizeof(unsigned char) * 3;

	auto u = (static_cast<double>(i) + RandomDouble()) / (screen_width - 1);
	auto v = (static_cast<double>(j) + RandomDouble()) / (screen_height - 1);

	/// if the ray intersects the triangle
	auto ray = Ray(camera.position, camera.GetDirectionFromUV(u, v));
	auto hit = Hit();

	/// navigate bvh
	root.hit(ray, hit);

	/// access the pixel like a 2d grid inverting the y
	auto pixel = (screen_height - 1 - j) * screen_width + i;
	auto pixel_idx = pixel * channels;

	/// render object
	if (hit.t < infinity)
	{
		WritePixel(buffer, pixel_idx, hit.color, samples);
		return;
	}
	/// background
	auto background = Vector3((double)j / screen_height, (double)i / screen_width, 0.25);
	WritePixel(buffer, pixel_idx,background, samples);
}


void Application::RenderBVH(const Camera& camera, const std::vector<Tri>& triList)
{
	/// build the BVH
	auto root_node = BVHNode(triList);

	/// create the buffer
	int channels = sizeof(unsigned char) * 3;
	auto buffer = std::shared_ptr<unsigned char[]>(new unsigned char[(screen_width * screen_height) * channels]);

	/// render : for each pixel
	for (int j = screen_height; j > -1; --j)
	{
		for (auto i = 0; i < screen_width; ++i)
		{
			RenderPixel(i, j, 1, root_node, camera, buffer.get());
		}
	}

	/// write the png
	stbi_write_png("image.png", screen_width, screen_height, channels, buffer.get(), screen_width * channels);
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
		bounding_box = AABB::MergeBounds(bounding_box, tri.GetBounds());
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
				file << ir << ' ' << ig << ' ' << ib << '\n';
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

void Application::WritePixel(unsigned char* buffer, int pixel, Vector3& colour, int samples)
{
	/// get the colours
	auto r = colour.x();
	auto g = colour.y();
	auto b = colour.z();

	/// scale by sample size
	auto scale = 1.0 / samples;
	r *= scale;
	g *= scale;
	b *= scale;

	/// write correct colour values
	auto ir = static_cast<int>(256 * std::clamp(r, 0.0, 1 - epsilon));
	auto ig = static_cast<int>(256 * std::clamp(g, 0.0, 1 - epsilon));
	auto ib = static_cast<int>(256 * std::clamp(b, 0.0, 1 - epsilon));

	/// write to buffer
	buffer[pixel + 0] += static_cast<char>(ir);
	buffer[pixel + 1] += static_cast<char>(ig);
	buffer[pixel + 2] += static_cast<char>(ib);
}
