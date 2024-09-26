#include "cell.h"
std::vector<sf::Color> cellAgeColor{sf::Color::Black, sf::Color::Red, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan, sf::Color::Blue, sf::Color::Magenta};
Cell::Cell() : cellShape(sf::Vector2f(1.0f, 1.0f))
{
	cellShape.setPosition(sf::Vector2f(0.0f, 0.0f));
	this->aliveColor = cellAgeColor.at(0);
	this->deadColor = sf::Color::White;
	cellShape.setFillColor(this->deadColor);
	this->cellSizeInPixels = 10;
	this->isCellAlive = false;
	this->cellAge = 0;
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
		if (input)
		{
			this->cellShape.setFillColor(this->aliveColor);
			this->cellAge = 0;
		}
		else
		{
			this->cellShape.setFillColor(this->deadColor);
			this->cellAge = 0;
		}
		this->isCellAlive = input;
		
	}
	else
	{
		if (this->isCellAlive)
		{
			//this->increase_cellAge();
		}
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

void Cell::increase_cellAge()
{
	this->cellAge++;
	if (this->cellAge < cellAgeColor.size())
	{
		this->aliveColor = cellAgeColor.at(this->cellAge);
		this->cellShape.setFillColor(this->aliveColor);
	}
	else
	{
		this->cellAge = 0;
		this->isCellAlive = false;
		this->cellShape.setFillColor(this->deadColor);
	}
}
void Cell::nullify_cellAge()
{
	this->cellAge = 0;
	this->aliveColor = cellAgeColor.at(0);
	if (this->isCellAlive)
	{
		this->cellShape.setFillColor(this->aliveColor);
	}
	else
	{
		this->cellShape.setFillColor(this->deadColor);
	}
}