#include <SFML/Graphics.hpp>

#include "application.h"

int main()
{
	Application* app = new Application();
	app->init();

	while (app->isRunning())
	{
		app->pollEvents();
		app->update();
		app->render();
	}

	app->close();

	return 0;
}