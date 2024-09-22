#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.h"
#include "LifeField.h"
#include <iostream>
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    
    std::vector<Cell> cellsVector{10};
    for (int i = 0; i < cellsVector.size(); i++)
    {
        Cell d{ sf::Vector2f(i * 20, 5),20 };
        cellsVector.at(i) = d;
    }
    CellularField field{ sf::Vector2f{40.0f, 40.0f}, sf::Vector2f{700.0f, 700.0f }, sf::Color::White, sf::Color::Red, 3.0f, sf::Vector2f(70, 70)};
    
    sf::Clock clock;
    int shift = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (clock.getElapsedTime().asMilliseconds() > 200)
        {
            field.testPatternDraw(TESTPATTERN::CHESS_PATTERN, shift);
            //std::cout << "test counter " << field.get_NumberOfCells_inFonNeimanSpace(1, 1) << std::endl;
            window.clear(sf::Color::Black);
            field.cellFieldDraw(window);
            window.display();
            shift++;
            clock.restart();
        }
    }

    return 0;
}