#include "cell.h"

Cell::Cell() : cellShape(sf::Vector2f(1.0f, 1.0f))
{
	cellShape.setPosition(sf::Vector2f(0.0f, 0.0f));
	this->aliveColor = sf::Color::Black;
	this->deadColor = sf::Color::White;
	cellShape.setFillColor(this->deadColor);
	this->cellSizeInPixels = 10;
	this->isCellAlive = false;
}

Cell::Cell(sf::Vector2f startPos, int sizeInPixels): Cell ()
{
	cellShape.setPosition(startPos);
	cellShape.setSize(sf::Vector2f(sizeInPixels, sizeInPixels));
}

void Cell::drawCell(sf::RenderWindow& inputWindow)
{
	inputWindow.draw(this->cellShape);
}
void Cell::set_isCellAlive(bool input)
{
	if (this->isCellAlive != input)
	{
		if (input) this->cellShape.setFillColor(this->aliveColor);
		else this->cellShape.setFillColor(this->deadColor);
		this->isCellAlive = input;
		
	}
	
}
bool Cell::get_isCellAlive()
{
	return this->isCellAlive;
}

bool Cell::get_isPointInCell(sf::Vector2f pointCoords)
{
	return this->cellShape.getGlobalBounds().contains(pointCoords);
}