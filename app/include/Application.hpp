#pragma once
#include <memory>

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

	void DrawBackground(std::ofstream& file, int i, int j);

private:
	const double screen_width = 1920.f / 4.f;
	const double screen_height = 1080.f / 4.f;
};
