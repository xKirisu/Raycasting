#ifndef _Observer
#define _Observer

#include "Ray.hpp"

enum Direction {
	up, down, left, right, rotateleft, rotateright
};
class Observer {
	sf::CircleShape shape;

	float rotation = 0;
	float moveSpeed;
	bool
		moveUp = false,
		moveDown = false,
		moveLeft = false,
		moveRight = false,
		rotateLeft = false,
		rotateRight = false;
public:
	Observer(sf::Vector2f start, sf::Color color, float moveSpeed = 128.0f) {
		shape.setPosition(start);
		this->moveSpeed = moveSpeed;

		shape.setFillColor(color);
		shape.setRadius(ObserverRadius);
	}
	void move(Direction set_direction, bool is_key_pressed);

	void draw(sf::RenderWindow& app, float tickrate);

	sf::Vector2f givePosition();
	float giveRotation();
};
#endif