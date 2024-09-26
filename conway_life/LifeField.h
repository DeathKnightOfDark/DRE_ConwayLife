#pragma once
#include <SFML/Graphics.hpp>
#include "cell.h"
#include <vector>
#include <math.h>
#include <map>
enum class TESTPATTERN
{
	CHESS_PATTERN,
	VERTICAL_STRIPE_PATTERN_EVEN, 
	VERTICAL_STRIPE_PATTERN_ODD, 
	HORIZONTAL_STRIPE_PATTERN_EVEN, 
	HORIZONTAL_STRIPE_PATTERN_ODD, 
	SIN_PATTERN
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

	uint8_t get_Byte_inFonNeimanSpace(int xPos, int yPos);
	uint8_t get_Byte_fromWolframSpace(int xPos, int yPos);
	void make_ConwayLife_iteration();
	void make_WolrframCellularAutomata_Iteration(uint8_t rule);
	sf::Vector2f get_cellShapeCoordsByPointCoords(sf::Vector2f coords);
	bool get_conditionOfOneCell(sf::Vector2f coords);
	void set_conditionOfOneCell(sf::Vector2f coords, bool input);
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