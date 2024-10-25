#pragma once
#include "libraries.h"
#include "Graphics.h"

class ShapeDrawer : Graphics
{
public:
	ShapeDrawer();

	sf::RectangleShape CreateSquare(float size, sf::Color color = sf::Color::Transparent, float posx = 0, float posy = 0, float OutlineThickness = 0, sf::Color OutlineColor = sf::Color::Transparent);
	sf::RectangleShape CreateRectangle(float sizex, float sizey, sf::Color color = sf::Color::Transparent, float posx = 0, float posy = 0, float OutlineThickness = 0, sf::Color OutlineColor = sf::Color::Transparent);
	sf::CircleShape CreateCircle(float radius, sf::Color color = sf::Color::Transparent, float posx = 0, float posy = 0, float OutlineThickness = 0, sf::Color OutlineColor = sf::Color::Transparent);
	sf::CircleShape CreateTriangle(float radius, sf::Color color = sf::Color::Transparent, float posx = 0, float posy = 0, float OutlineThickness = 0, sf::Color OutlineColor = sf::Color::Transparent);
	sf::CircleShape CreatePolygon(float radius, int sideNumber, sf::Color color = sf::Color::Transparent, float posx = 0, float posy = 0, float OutlineThickness = 0, sf::Color OutlineColor = sf::Color::Transparent);
};
