#pragma once
#include <memory>

class Application
{
public:
	static std::unique_ptr<Application> Create();
	~Application() = default;

public:
	void run();

private:
	Application() = default;
};
