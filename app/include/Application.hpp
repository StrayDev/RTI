#pragma once
#include <memory>
#include <vector>
#include "Vector3.hpp"

class Tri;
class Camera;

class Application
{
public:
	static std::unique_ptr<Application> Create();
	~Application() = default;

public:
	void init();
	void run();

private:
	Application() = default;

	void RenderBasic(const std::vector<Tri>& tri_list, const Camera& camera);
	void RenderBVH(const Camera& camera, const std::vector<Tri>& triList);
	void RenderBVHThreaded(const Camera& camera, const std::vector<Tri>& triList);

	void WritePixel(unsigned char* buffer, int pixel, Vector3& colour);
	void DrawBackground(std::ofstream& file, int i, int j);

private:
	const int screen_width = 1920;
	const int screen_height = 1080;
};
