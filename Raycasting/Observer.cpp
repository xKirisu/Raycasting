#include <SFML/Graphics.hpp>
#include "Observer.hpp"

void Observer::move(Direction set_direction, bool is_key_pressed) {
	switch (set_direction)
	{
	case up:
		if (is_key_pressed) moveUp = true;
		else moveUp = false;
		break;
	case down:
		if (is_key_pressed) moveDown = true;
		else moveDown = false;
		break;
	case left:
		if (is_key_pressed) moveLeft = true;
		else moveLeft = false;
		break;
	case right:
		if (is_key_pressed) moveRight = true;
		else moveRight = false;
		break;
	case rotateleft:
		if (is_key_pressed) rotateLeft = true;
		else rotateLeft = false;
		break;
	case rotateright:
		if (is_key_pressed) rotateRight = true;
		else rotateRight = false;
		break;
	}
}
void Observer::draw(sf::RenderWindow& app, float tickrate) {
	if (moveUp) {
		shape.move(0, -moveSpeed * tickrate);
	}
	if (moveDown) {
		shape.move(0, moveSpeed * tickrate);
	}
	if (moveLeft) {
		shape.move(-moveSpeed * tickrate, 0);
	}
	if (moveRight) {
		shape.move(moveSpeed * tickrate, 0);
	}
	if (rotateLeft) {
		rotation -= tickrate * 150;
	}
	if (rotateRight) {
		rotation += tickrate * 150;
	}

	app.draw(shape);
}

sf::Vector2f Observer::givePosition() {
	return shape.getPosition();
}
float Observer::giveRotation() {
	return rotation;
}