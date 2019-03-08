#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow* window, int rows, int cols);

	sf::Color background;

	void drawGrid();
	void drawCells();
	void calculateNextGeneration();

	~Game();

private:
	sf::RenderWindow* window;

	bool* cells;

	int cols;
	int rows;

	bool getCell(int x, int y);
	void setCell(int x, int y, bool value);
	void randomizeCells();
};