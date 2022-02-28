#include "Application.hpp"

int main()
{
	auto app = Application::Create();
	app->init();
	app->run();
	return 0;
}
