#ifndef _Ray
#define _Ray

#define ObserverRadius 32
#define RayCouter 64
#define RenderDistance 400.0
#define AngleGap 1.45

class Ray {

	sf::Color color = sf::Color::Transparent;
	float distance;

	sf::Vector2f start;
	sf::Vector2f end;

	sf::Color raycolor = sf::Color::Red;
public:
	Ray() {}
	Ray(sf::Color color) : raycolor(color){}

	void Render(sf::RenderWindow& app, float tickrate, sf::Vector2f observer_position, int observer_rotation, std::vector<sf::RectangleShape> mapBlocks, int angle);
	void Draw3D(sf::RenderWindow& app, float WinX, float WinY, int i);

};
#endif // _Ray
