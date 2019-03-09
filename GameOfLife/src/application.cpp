#include "application.h"

void Application::init()
{
	mainWindow = new sf::RenderWindow(sf::VideoMode(700, 700), "Conway's Game of Life");
	mainWindow->setFramerateLimit(30);
	game = new Game(mainWindow, 100, 100);
	game->background = sf::Color(255, 255, 255, 255); // white
}

void Application::pollEvents()
{
	sf::Event event;
	while (mainWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mainWindow->close();
	}
}

void Application::update()
{
	game->calculateNextGeneration();
}

void Application::render()
{
	mainWindow->clear(game->background);
	
	game->drawGrid();
	game->drawCells();

	mainWindow->display();
}


bool Application::isRunning()
{
	return mainWindow->isOpen();
}

sf::RenderWindow * Application::getWindow()
{
	return mainWindow;
}

void Application::close()
{
	game->~Game();
}
