#include "Application.hpp"
#include "AABB.hpp"
#include "BVHNode.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "ObjLoader.hpp"
#include "Ray.hpp"
#include "Settings.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

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

	/// testing import of tiny obj
	auto objloader = ObjLoader();
	objloader.LoadObj("bunny.obj", "bunny");
	auto bunny_1 = objloader.CreateObject("bunny");

/*	/// perspective matrix
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);

	/// Camera matrix
	glm::mat4 View = glm::lookAt(glm::vec3(0, 2, 1), // Camera position in World Space
	  						   glm::vec3(0, 0, 0), // and looks at the origin
								  glm::vec3(0, 1, 0));// Head is up (set to 0,-1,0 to look upside-down)

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 translation = glm::translate(glm::mat4(1), {0,0,0});
	glm::mat4 rotation(1);
	glm::mat4 scale(1);

	glm::mat4 Model = translation * rotation * scale; // = translation * rotation * scale
													 // Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Model; //Projection * View * Model;   // Remember, matrix multiplication is the other way around

	std::cout << "[" << MVP[0][0] << "] [" << MVP[0][1] << "] [" << MVP[0][2] << "] [" << MVP[0][3] << "]" << '\n';
	std::cout << "[" << MVP[1][0] << "] [" << MVP[1][1] << "] [" << MVP[1][2] << "] [" << MVP[1][3] << "]" << '\n';
	std::cout << "[" << MVP[2][0] << "] [" << MVP[2][1] << "] [" << MVP[2][2] << "] [" << MVP[2][3] << "]" << '\n';
	std::cout << "[" << MVP[3][0] << "] [" << MVP[3][1] << "] [" << MVP[3][2] << "] [" << MVP[3][3] << "]" << '\n';

	std::cout << "X ?? : " << MVP[0][0] + MVP[1][0] + MVP[2][0] + MVP[3][0] << '\n';
	std::cout << "Before  : " << bunny_1->triangles[0].GetVertices().begin()->x() << '\n';*/

	//auto vec = glm::vec4(translation * glm::vec4(v.x(), v.y(), v.z(), 0.0f));
	std::cout << "before : " << bunny_1->triangles[0].GetVertices().begin()->x() << '\n';

	for (auto& t : bunny_1->triangles)
	{
		for (auto& v : t.GetVertices())
		{
			v.value[0] += 1.0f;
			v.value[1] += .01f;
			v.value[2] += .01f;
		}
	}

	std::cout << "After  : " << bunny_1->triangles[0].GetVertices().begin()->x() << '\n';

	/// create the camera
	auto camera = Camera(Vector3{ 0, 1, 2 }, Vector3{ 0, 0, 1 });/// direction not in yet

	/// render methods
	//RenderBasic(triList, camera);
	RenderBVH(camera, bunny_1->triangles);

	/// stop the timer and print result
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << "\n Write time      : " << duration.count() / 1000.f << '\n';
}

void Application::RenderBVH(const Camera& camera, const std::vector<Tri>& triList)
{
	/// build the BVH
	auto root_node = BVHNode(triList);

	/// Create file
	auto file = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
	file << "P3\n"
		 << screen_width << " " << screen_height << "\n255\n";

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
