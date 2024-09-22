#include "LifeField.h"

#include <iostream>
CellularField::CellularField() : CellularField(sf::Vector2f{20.0f, 20.0f},sf::Vector2f{500.0f, 500.0f},sf::Color::White, sf::Color::Red,3.0f, sf::Vector2f{50, 50})
{
	
}
CellularField::CellularField(sf::Vector2f inputStartPoint, sf::Vector2f inputSize, sf::Color bgColor, sf::Color borderColor, float borderWidth, sf::Vector2f cellTableDimensionSizes) : backgroundField{inputStartPoint}
{
	this->startPoint = inputStartPoint;
	this->height = inputSize.y;
	this->width = inputSize.x;
	this->borderColor = borderColor;
	this->backgroundColor = bgColor;
	this->borderWidth = borderWidth;
	this->backgroundField.setPosition(startPoint);
	this->backgroundField.setOutlineThickness((float)this->borderWidth);
	this->backgroundField.setOutlineColor(this->borderColor);
	this->backgroundField.setFillColor(this->backgroundColor);
	this->backgroundField.setSize(sf::Vector2f{(float)(this->width), (float)(this->height )});
	int oneCellWidth = (int)(this->width / cellTableDimensionSizes.x);
	int oneCellHeight = (int)(this->height / cellTableDimensionSizes.y);
	for (int i = 0; i < (int)cellTableDimensionSizes.y; i++)
	{
		this->cells.push_back(std::vector<Cell>{});
		for (int j = 0; j < (int)cellTableDimensionSizes.x; j++)
		{
			this->cells.at(i).push_back(Cell{ sf::Vector2f{this->startPoint.x +   j* (float)(oneCellWidth), this->startPoint.y + i* (float)(oneCellHeight)},oneCellWidth });
		}

	}
}
void CellularField::cellFieldDraw(sf::RenderWindow& drawableWindow)
{
	drawableWindow.draw(this->backgroundField);
	for (auto heightIt = this->cells.begin(); heightIt != this->cells.end(); heightIt++)
	{
		for (auto widthIt = heightIt->begin(); widthIt != heightIt->end(); widthIt++)
		{
			widthIt->drawCell(drawableWindow);
		}
	}
}

void CellularField::set_startPoint(sf::Vector2f newStartPoint)
{
	this->startPoint = newStartPoint;
	this->backgroundField.setPosition(this->startPoint);
}

void CellularField::testPatternDraw(TESTPATTERN inputPattern, int shift = 0)
{
	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells.at(i).size(); j++)
		{
			int rest = 0;
			switch (inputPattern)
			{
			case TESTPATTERN::CHESS_PATTERN:
				{
				rest = (shift + i + j) % 2;
					break;
				}
			case TESTPATTERN::VERTICAL_STRIPE_PATTERN_EVEN:
			{
				rest = (((shift + j)%2)==0? 1 : 0 );
				break;
			}
			case TESTPATTERN::VERTICAL_STRIPE_PATTERN_ODD:
			{
				rest = (((shift + j) % 2) != 0 ? 1 : 0);
				break;
			}
			case TESTPATTERN::HORIZONTAL_STRIPE_PATTERN_EVEN:
			{
				rest = (((shift + i) % 2) == 0 ? 1 : 0);
				break;
			}
			case TESTPATTERN::HORIZONTAL_STRIPE_PATTERN_ODD:
			{
				rest = (((shift + i) % 2) != 0 ? 1 : 0);
				break;
			}
			}
			((rest == 1) ? this->cells.at(i).at(j).set_isCellAlive(true) : this->cells.at(i).at(j).set_isCellAlive(false));
			//std::cout << "rest " << rest << std::endl;
		}
	}
	
}

int CellularField::get_NumberOfCells_inFonNeimanSpace(int xPos, int yPos)
{
	if ((yPos < 0) || (yPos >= this->cells.size())) return -1;
	if ((xPos<0)||(xPos>=this->cells.at(yPos).size())) return -1;
	//int lowestY = (yPos - 1 >= 0) ? (yPos - 1) : this->cells.size() - 1;
	int leftUPY = (yPos - 1 >= 0) ? (yPos - 1) : this->cells.size() - 1;
	//int highestY = (yPos + 1 < this->cells.size()) ? (yPos + 1) : 0;
	int rightLowY = (yPos + 1 < this->cells.size()) ? (yPos + 1) : 0;
	int leftUpX = (xPos - 1 >= 0) ? (xPos - 1) : (this->cells.at(leftUPY).size() - 1);
	int rightLowX = (xPos + 1 < this->cells.at(rightLowY).size()) ? (xPos + 1) : 0;
	std::vector<int> xPoses{leftUpX, xPos, rightLowX};
	std::vector<int> yPoses{leftUPY, yPos, rightLowY};
	std::sort(xPoses.begin(), xPoses.end());
	std::sort(yPoses.begin(), yPoses.end());
	int returnResult = 0;
	for (auto itY = yPoses.begin(); itY != yPoses.end(); itY++)
	{
		for (auto itX = xPoses.begin(); itX != xPoses.end(); itX++)
		{
			(this->cells.at(*itY).at(*itX).get_isCellAlive()) ? returnResult++ : (returnResult+=0);
		}
	}
	return returnResult;
}