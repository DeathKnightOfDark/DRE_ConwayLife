#pragma once
#include <SFML/Graphics.hpp>
#include "cell.h"
#include <vector>
enum class TESTPATTERN
{
	CHESS_PATTERN,
	VERTICAL_STRIPE_PATTERN_EVEN, 
	VERTICAL_STRIPE_PATTERN_ODD, 
	HORIZONTAL_STRIPE_PATTERN_EVEN, 
	HORIZONTAL_STRIPE_PATTERN_ODD 
};
class CellularField
{
public:
	CellularField();
	CellularField(sf::Vector2f inputStartPoint, sf::Vector2f inputSize, sf::Color bgColor, sf::Color borderColor, float borderWidth, sf::Vector2f cellTableDimensionSizes);
	void cellFieldDraw(sf::RenderWindow& drawableWindow);
	void set_startPoint(sf::Vector2f newStartPoint);
	void testPatternDraw(TESTPATTERN inputPattern, int shift );
	int get_NumberOfCells_inFonNeimanSpace(int xPos, int yPos);
	private: 
		sf::Vector2f startPoint;
		float height;
		float width;
		sf::RectangleShape backgroundField;
		sf::Color borderColor;
		sf::Color backgroundColor;
		float borderWidth;
		std::vector<std::vector<Cell>> cells;

};