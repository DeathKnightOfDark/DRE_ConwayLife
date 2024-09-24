#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.h"
#include "LifeField.h"
#include <iostream>

void do_mouse_input(sf::RenderWindow &window, CellularField &cellField)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f cellpos = cellField.get_cellShapeCoordsByPointCoords(sf::Vector2f{(float)mousePos.x, (float)mousePos.y});
    std::cout << cellpos.x << " " << cellpos.y << std::endl;
    cellField.set_conditionOfOneCell(cellpos, cellField.get_conditionOfOneCell(cellpos));
}

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
    CellularField field{ sf::Vector2f{40.0f, 40.0f}, sf::Vector2f{700.0f, 700.0f }, sf::Color::White, sf::Color::Red, 3.0f, sf::Vector2f(100, 100)};
    
    sf::Clock clock;
    int shift = 42;
    field.testPatternDraw(TESTPATTERN::SIN_PATTERN, shift);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //std::cout << "clicking mouse" << std::endl;
            do_mouse_input(window, field);
        }
        if (clock.getElapsedTime().asMilliseconds() > 1000)
        {
            field.make_ConwayLife_iteration();
            //std::cout << "test counter " << field.get_NumberOfCells_inFonNeimanSpace(1, 1) << std::endl;
            window.clear(sf::Color::Black);
            field.cellFieldDraw(window);
            window.display();
            
            clock.restart();
        }
    }

    return 0;
}