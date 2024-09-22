#pragma once
#include <SFML/Graphics.hpp>
class Cell
{
public:
	Cell();
	Cell(sf::Vector2f startPos, int sizeInPixels);
	void drawCell(sf::RenderWindow &inputWindow);
	void set_isCellAlive(bool input);
	bool get_isCellAlive();

private:
	sf::RectangleShape cellShape;
	sf::Vector2f cellStartPosition;
	int cellSizeInPixels;
	bool isCellAlive;
	sf::Color aliveColor;
	sf::Color deadColor;
};