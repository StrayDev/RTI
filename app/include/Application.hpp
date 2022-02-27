#pragma once
#include <memory>

#include "Camera.hpp"

class Application
{
public:
	static std::unique_ptr<Application> Create();
	~Application() = default;

public:
	void run();

private:
	Application() = default;

private:
	std::unique_ptr<Camera> camera { nullptr };
};
