#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.h"
#include "LifeField.h"
#include <iostream>

void do_mouse_input(sf::RenderWindow &window, CellularField &cellField)
{
    static sf::Vector2i prevMousePos = sf::Vector2i{ 0,0 };
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (mousePos != prevMousePos)
    {
        sf::Vector2f cellpos = cellField.get_cellShapeCoordsByPointCoords(sf::Vector2f{(float)mousePos.x, (float)mousePos.y});
        std::cout << cellpos.x << " " << cellpos.y << std::endl;
        cellField.set_conditionOfOneCell(cellpos, true);
    }

    prevMousePos = mousePos;
}

int main()
{
    bool runLife = false;
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
    sf::Clock inputClock;
    int shift = 22;
    uint8_t rule = 110;
    field.testPatternDraw(TESTPATTERN::SIN_PATTERN, shift);
    
    bool isMouseAlreadyClicked = false;
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
            if (inputClock.getElapsedTime().asMilliseconds() > 200)
            {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                runLife = !runLife;
                std::cout << "space called" << std::endl;
                inputClock.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                shift += 10;
                field.testPatternDraw(TESTPATTERN::SIN_PATTERN, shift);
                inputClock.restart();
                rule+=11;
            }
            
            }
       
        if (clock.getElapsedTime().asMilliseconds() > 100)
        {
           
            if (runLife)
            {
                //field.make_ConwayLife_iteration(3,7, 1, 6);
                field.make_WolrframCellularAutomata_Iteration(rule);
                //std::cout << "test counter " << field.get_NumberOfCells_inFonNeimanSpace(1, 1) << std::endl;
            }
            window.clear(sf::Color::Black);
            field.cellFieldDraw(window);
            window.display();
            clock.restart();
        }
    }

    return 0;
}