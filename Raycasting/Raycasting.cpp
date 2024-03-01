#define _WIN32_WINNT 0x0500
#define WindowSizeX 900
#define WindowSizeY 900

#define BlockSizeRE 96
#define MapSize 10

#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Observer.hpp"
#include "Ray.hpp"

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    sf::RenderWindow window2D(sf::VideoMode(WindowSizeX, WindowSizeY), "RayCasting2D");
    sf::RenderWindow window3D(sf::VideoMode(WindowSizeX, WindowSizeY), "RayCasting3D");
    window2D.setPosition(sf::Vector2i(50, 150));
    window3D.setPosition(sf::Vector2i(window2D.getPosition().x + window2D.getSize().x, window2D.getPosition().y));

    sf::RectangleShape celling;
    celling.setFillColor(sf::Color(55, 55, 55));
    celling.setSize(sf::Vector2f(WindowSizeX, WindowSizeY / 2));

    using namespace re;

    Observer observer(sf::Vector2f(520, 585), sf::Color(0, 0, 128));
    Ray rays[RayCouter];
    Ray coreray(sf::Color::Yellow);

    // Map initate ////////////////////////////////////////////
    sf::Uint8 map[MapSize][MapSize] = {
        {3, 3, 3, 1, 1, 1, 1, 1, 1, 1},
        {3, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {3, 3, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    std::vector<sf::RectangleShape> blocks;

    for (sf::Uint8 y = 0; y < MapSize; y++)
        for (sf::Uint8 x = 0; x < MapSize; x++) {
            
            sf::RectangleShape block;
            block.setSize(sf::Vector2f(BlockSizeRE, BlockSizeRE));

            switch (map[y][x])
            {
            case 1:
                block.setFillColor(sf::Color::White);
                break;
            case 2:
                block.setFillColor(sf::Color::Cyan);
                break;
            case 3:
                block.setFillColor(sf::Color::Yellow);
                break;
            case 4:
                block.setFillColor(sf::Color::Magenta);
                break;
            default:
                block.setFillColor(sf::Color::Transparent);
                break;
            }

            block.setPosition(x * BlockSizeRE, y * BlockSizeRE);

            blocks.push_back(block);
        }

    // /////////////////////////////////////////////////////////////

    sf::Clock tick;
    float tickrate;
    while (window2D.isOpen()&&window3D.isOpen())
    {
        sf::Event event;
        while (window2D.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window2D.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) observer.move(up,  true);
                if (event.key.code == sf::Keyboard::S) observer.move(down, true);
                if (event.key.code == sf::Keyboard::A) observer.move(left, true);
                if (event.key.code == sf::Keyboard::D) observer.move(right, true);
                if (event.key.code == sf::Keyboard::Q) observer.move(rotateleft, true);
                if (event.key.code == sf::Keyboard::E) observer.move(rotateright, true);
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) observer.move(up, false);
                if (event.key.code == sf::Keyboard::S) observer.move(down, false);
                if (event.key.code == sf::Keyboard::A) observer.move(left, false);
                if (event.key.code == sf::Keyboard::D) observer.move(right, false);
                if (event.key.code == sf::Keyboard::Q) observer.move(rotateleft, false);
                if (event.key.code == sf::Keyboard::E) observer.move(rotateright, false);
            }
        }
        while (window3D.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window3D.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) observer.move(up, true);
                if (event.key.code == sf::Keyboard::S) observer.move(down, true);
                if (event.key.code == sf::Keyboard::A) observer.move(left, true);
                if (event.key.code == sf::Keyboard::D) observer.move(right, true);
                if (event.key.code == sf::Keyboard::Q) observer.move(rotateleft, true);
                if (event.key.code == sf::Keyboard::E) observer.move(rotateright, true);
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) observer.move(up, false);
                if (event.key.code == sf::Keyboard::S) observer.move(down, false);
                if (event.key.code == sf::Keyboard::A) observer.move(left, false);
                if (event.key.code == sf::Keyboard::D) observer.move(right, false);
                if (event.key.code == sf::Keyboard::Q) observer.move(rotateleft, false);
                if (event.key.code == sf::Keyboard::E) observer.move(rotateright, false);
            }
        }

        tickrate = tick.restart().asSeconds();
        window2D.clear();
            observer.draw(window2D, tickrate);

            for (sf::RectangleShape block : blocks) {
                window2D.draw(block);
            }
            for (int i = 0; i < RayCouter; i++) {
                rays[i].Render(window2D, tickrate, observer.givePosition(), observer.giveRotation(), blocks, i);
            }

            coreray.Render(window2D, tickrate, observer.givePosition(), observer.giveRotation(), blocks, (RayCouter/2));
            
        window2D.display();

        window3D.clear(sf::Color(33, 33, 33));
        window3D.draw(celling);
            for (int i = 0; i < RayCouter; i++)
                rays[i].Draw3D(window3D, WindowSizeX, WindowSizeY, i);
        window3D.display();
    }

    return 0;
}