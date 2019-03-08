#include <cstdlib>
#include <iostream>

#include "game.h"

Game::Game(sf::RenderWindow* window, int rows, int cols)
{
	this->window = window;

	this->rows = rows;
	this->cols = cols;

	this->cells = new bool[rows * cols];
	randomizeCells();
}

bool Game::getCell(int x, int y)
{
	return cells[rows * y + x];
}

void Game::setCell(int x, int y, bool value)
{
	cells[rows * y + x] = value;
}

void Game::drawGrid()
{
	// vertical
	for (int i = 0; i < cols; i++)
	{
		sf::RectangleShape line(sf::Vector2f(1.0f, window->getSize().y));
		line.setPosition((window->getSize().x / rows) * i, 0);
		line.setFillColor(sf::Color::Black);

		window->draw(line);
	}

	// horizontal
	for (int i = 0; i < rows; i++)
	{
		sf::RectangleShape line(sf::Vector2f(window->getSize().x, 1.0f));
		line.setPosition(0, (window->getSize().y / cols) * i);
		line.setFillColor(sf::Color::Black);

		window->draw(line);
	}
}

void Game::drawCells()
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (getCell(i, j))
			{
				sf::RectangleShape cell(sf::Vector2f(window->getSize().x / rows, window->getSize().y / cols));
				cell.setPosition((window->getSize().x / rows) * i, (window->getSize().y / cols) * j);
				cell.setFillColor(sf::Color::Black);

				window->draw(cell);
			}
		}
	}
}

void Game::calculateNextGeneration()
{
	bool* buffer = new bool[rows * cols];

	for (int i = 0; i < rows * cols; i++)
	{
		buffer[i] = cells[i];
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			/* Calculate neighbours */
			int neighbours = 0;

			// straight
			if (i > 0 && getCell(i - 1, j))                              neighbours++;
			if (i < cols - 1 && getCell(i + 1, j))                       neighbours++;
			if (j > 0 && getCell(i, j - 1))                              neighbours++;
			if (j < rows - 1 && getCell(i, j + 1))                       neighbours++;

			// diagonal
			if ((i > 0 && j > 0) && getCell(i - 1, j - 1))               neighbours++;
			if ((i > 0 && j < cols - 1) && getCell(i - 1, j + 1))        neighbours++;
			if ((i < rows - 1 && j > 0) && getCell(i + 1, j - 1))        neighbours++;
			if ((i < rows - 1 && j < cols - 1) && getCell(i + 1, j + 1)) neighbours++;

			/* Change cell */
			if (getCell(i, j) && neighbours < 2) buffer[rows * j + i] = false;
			if (getCell(i, j) && (neighbours == 2 || neighbours == 3)) buffer[rows * j + i] = true;
			if (getCell(i, j) && neighbours > 3) buffer[rows * j + i] = false;
			if (!getCell(i, j) && neighbours == 3) buffer[rows * j + i] = true;
		}
	}

	cells = buffer;
}

void Game::randomizeCells()
{
	std::srand(std::time(0));
	for (int i = 0; i < rows * cols; i++)
	{
		(std::rand() % 2) == 0 ? (cells[i] = 0) : (cells[i] = 1);

		// DEBUG
		std::cout << (int)cells[i] << " ";
		if ((i + 1) % cols == 0) std::cout << std::endl;
		//
	}
}

Game::~Game()
{
	delete cells;
}

