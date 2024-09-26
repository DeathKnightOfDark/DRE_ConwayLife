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
			case TESTPATTERN::SIN_PATTERN: 
			{
				double d = std::sin((double)(i * j * shift));
				if (d >= 0.5) rest = 1;
				else rest = 0;
				break;
			}
			case TESTPATTERN::SQUARE_CENTRAL: 
			{
				if ((i >= 30) && (i <= 60) && (j >= 30) && (j <= 60)) rest = 1;
				else rest = 0;
				break;
			}
			case TESTPATTERN::CLEAR_PATTERN:
			{
				rest = 0;
				break;
			}
			}
			this->cells.at(i).at(j).nullify_cellAge();
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
			if (!((*itY==yPos)&&(*itX==xPos))) (this->cells.at(*itY).at(*itX).get_isCellAlive()) ? returnResult++ : (returnResult+=0);
			
		}
	}
	return returnResult;
}

uint8_t CellularField::get_Byte_fromWolframSpace(int xPos, int yPos)
{
	if ((yPos < 0) || (yPos >= this->cells.size())) return 0xFF;
	if ((xPos < 0) || (xPos >= this->cells.at(yPos).size())) return 0xFF;
	int xPrevPos, xNextPos;
	if (xPos - 1 >= 0) xPrevPos = xPos - 1;
	else xPrevPos = this->cells.at(yPos).size() - 1;
	if (xPos + 1 < this->cells.at(yPos).size()) xNextPos = xPos + 1;
	else xNextPos = 0;
	uint8_t returnResult = 0;
	if (this->cells.at(yPos).at(xPrevPos).get_isCellAlive()) returnResult = returnResult | 0x1;
	if (this->cells.at(yPos).at(xPos).get_isCellAlive()) returnResult = returnResult | 0x2;
	if (this->cells.at(yPos).at(xNextPos).get_isCellAlive()) returnResult = returnResult | 0x4;
	return returnResult;
	
}

void CellularField::make_WolrframCellularAutomata_Iteration(uint8_t rule)
{
	std::map<uint8_t, bool> ruleMap;
	for (uint8_t i = 0; i < 8; i++)
	{
		ruleMap[i] = (((rule >> i) & 0x1) == 1);
	}
	std::vector < std::vector<bool>> newConditionBuffer;
	for (int i = 0; i < this->cells.size(); i++)
	{
		std::vector<bool> rowNewCond;
		for (int j = 0; j < this->cells.at(i).size(); j++)
		{
			uint8_t cellnum = this->get_Byte_fromWolframSpace(j, i);
			if (cellnum != 0xFF)
			{
				rowNewCond.push_back(ruleMap[cellnum]);
			}
			else rowNewCond.push_back(false);
		}
		newConditionBuffer.push_back(rowNewCond);
	}
	for (int i = 0; i < this->cells.size(); i++)
	{

		for (int j = 0; j < this->cells.at(i).size(); j++)
		{
			this->cells.at(i).at(j).set_isCellAlive(newConditionBuffer.at(i).at(j));
		}
	}

}
uint8_t CellularField::get_Byte_inFonNeimanSpace(int xPos, int yPos)
{
	return 0;
}

void CellularField::make_ConwayLife_iteration(int cellsToBirthMin, int cellsToBirthMax, int minCellsToSurvive, int maxCellsToSurvive)
{
	std::vector<std::vector<bool>> newLifeConditionBuffer;
	for (int i = 0; i < this->cells.size(); i++)
	{
		std::vector<bool> rowBuffer;
		for (int j = 0; j < this->cells.at(i).size(); j++)
		{
			int livingCellsCounter = this->get_NumberOfCells_inFonNeimanSpace(j, i);
			//std::cout << "livingCellsCounter " << livingCellsCounter << std::endl;
			bool inputVal = false;
			if (this->cells.at(i).at(j).get_isCellAlive())
			{
				
				if ((livingCellsCounter == minCellsToSurvive) || (livingCellsCounter == maxCellsToSurvive))
				{
					inputVal = true;
					
				}
				else inputVal = false;
			}
			else
			{
				
				if ((livingCellsCounter >= cellsToBirthMin)&&(livingCellsCounter<=cellsToBirthMax)) inputVal = true;
				else inputVal = false;
			}
			rowBuffer.push_back(inputVal);
		}
		newLifeConditionBuffer.push_back(rowBuffer);
	}

	for (int i = 0; i < this->cells.size(); i++)
	{

		for (int j = 0; j < this->cells.at(i).size(); j++)
		{
			this->cells.at(i).at(j).set_isCellAlive(newLifeConditionBuffer.at(i).at(j));
		}
	}
}

sf::Vector2f CellularField::get_cellShapeCoordsByPointCoords(sf::Vector2f coords)
{
	for (int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells.at(i).size();j++)
		{
			if (this->cells.at(i).at(j).get_isPointInCell(coords)) return sf::Vector2f{(float)j, float(i)};
		}
	}
	return sf::Vector2f{-1.0f, -1.0f};
}

bool CellularField::get_conditionOfOneCell(sf::Vector2f coords)
{
	if (coords.y >= 0 && coords.y < this->cells.size())
	{
		if (coords.x >= 0 && coords.x < this->cells.at((int)coords.y).size())
		{
			return this->cells.at((int)coords.y).at((int)coords.x).get_isCellAlive();
		}
		else return false;
	}
	else return false;
	return false;
}
void CellularField::set_conditionOfOneCell(sf::Vector2f coords, bool input)
{
	if (coords.y >= 0 && coords.y < this->cells.size())
	{
		if (coords.x >= 0 && coords.x < this->cells.at((int)coords.y).size())
		{
			this->cells.at((int)coords.y).at((int)coords.x).set_isCellAlive(input);
		}
		
	}
	
}