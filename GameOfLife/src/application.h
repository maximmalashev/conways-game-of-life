#pragma once

#include <SFML/Graphics.hpp>

#include "game.h"

class Application
{
public:
	void init();
	void pollEvents();
	void update();
	void render();
	void close();

	bool isRunning();
	sf::RenderWindow* getWindow();

private:
	sf::RenderWindow* mainWindow;
	Game* game;
};