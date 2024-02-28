#include <SFML/Graphics.hpp>
#include "Ray.hpp"
#include <iostream>
#define PI 3.14159265


void Ray::Render(sf::RenderWindow& app, float tickrate, sf::Vector2f observer_position, int observer_rotation, std::vector<sf::RectangleShape> mapBlocks, int angle) {
	start = observer_position + sf::Vector2f(ObserverRadius, ObserverRadius);
	end = observer_position + sf::Vector2f(ObserverRadius, ObserverRadius);

	if (observer_rotation == 0) {
		observer_rotation = 1;
	}

	float radian = (angle*AngleGap) * PI / 180 + observer_rotation * PI / 180;
	sf::Vector2f jump(ObserverRadius / 8 * std::cos(radian), ObserverRadius / 8 * std::sin(radian));


	// Jump and check
	bool inBlock = false;
	while (!inBlock) {
		end -= jump;

		for (sf::RectangleShape block : mapBlocks) {
			if (block.getGlobalBounds().contains(end) && block.getFillColor() != sf::Color::Transparent) {
				inBlock = true;
				color = block.getFillColor();

			}
		}

		distance = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
		if (distance > RenderDistance) {
			inBlock = true;
			color = sf::Color::Transparent;
		}
	}

	float angleIndex = (RayCouter / 2 * AngleGap) - angle * AngleGap;
	float a = angleIndex * PI / 180;
	if (a < 0) a += 2 * PI;
	if (a > 2 * PI) a -= 2 * PI;

	float factor = std::cos(a);
	distance = distance * factor;

	sf::VertexArray vertex(sf::Lines, 2);
	vertex[0].position = start;
	vertex[0].color = raycolor;
	vertex[1].position = end;
	vertex[1].color = raycolor;


	app.draw(vertex);
}

void Ray::Draw3D(sf::RenderWindow& app, float winX, float winY, int i) {
	sf::RectangleShape block;
	float screenDistance = distance / RenderDistance;

	sf::Color setcolor;
	
	if (color != sf::Color::Transparent) {
		sf::Uint8 grayscale = color.r * 0.55 + color.g * 0.55 + color.b * 0.55;
		sf::Uint8 red =  color.r * (1 - screenDistance);
		sf::Uint8 green = color.g * (1 - screenDistance);
		sf::Uint8 blue = color.b * (1 - screenDistance);

		setcolor = sf::Color(red, green, blue);
	}
	else {
		setcolor = sf::Color::Transparent;
	}

	block.setFillColor(setcolor);

	float height = (1 - distance / RenderDistance) * winY;
	float position = winY / 2 - (1 - distance / RenderDistance) * winY/2;

	block.setSize(sf::Vector2f(winX / RayCouter, height));
	block.setPosition(i * (winX / RayCouter), position);

	app.draw(block);
}
