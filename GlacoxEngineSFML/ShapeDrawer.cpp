#include "ShapeDrawer.h"

ShapeDrawer::ShapeDrawer()
{
}

sf::RectangleShape ShapeDrawer::CreateSquare(float size, sf::Color color, float posx, float posy, float OutlineThickness, sf::Color OutlineColor)
{
	sf::RectangleShape square(sf::Vector2f(size, size));
	square.setFillColor(color);
	square.setPosition(sf::Vector2f(posx, posy));

	square.setOutlineThickness(OutlineThickness);
	square.setOutlineColor(OutlineColor);

	return square;
}

sf::RectangleShape ShapeDrawer::CreateRectangle(float sizex, float sizey, sf::Color color, float posx, float posy, float OutlineThickness, sf::Color OutlineColor)
{
	sf::RectangleShape rectangle(sf::Vector2f(sizex, sizey));
	rectangle.setFillColor(color);
	rectangle.setPosition(sf::Vector2f(posx, posy));

	rectangle.setOutlineThickness(OutlineThickness);
	rectangle.setOutlineColor(OutlineColor);

	return rectangle;
}

sf::CircleShape ShapeDrawer::CreateCircle(float radius, sf::Color color, float posx, float posy, float OutlineThickness, sf::Color OutlineColor)
{
	sf::CircleShape circle(radius);
	circle.setFillColor(color);
	circle.setPosition(sf::Vector2f(posx, posy));

	circle.setOutlineThickness(OutlineThickness);
	circle.setOutlineColor(OutlineColor);

	return circle;
}

sf::CircleShape ShapeDrawer::CreateTriangle(float radius, sf::Color color, float posx, float posy, float OutlineThickness, sf::Color OutlineColor)
{
	sf::CircleShape triangle(radius, 3);
	triangle.setFillColor(color);
	triangle.setPosition(sf::Vector2f(posx, posy));

	triangle.setOutlineThickness(OutlineThickness);
	triangle.setOutlineColor(OutlineColor);

	return triangle;
}

sf::CircleShape ShapeDrawer::CreatePolygon(float radius, int sideNumber, sf::Color color, float posx, float posy, float OutlineThickness, sf::Color OutlineColor)
{
	sf::CircleShape polygon(radius, sideNumber);
	polygon.setFillColor(color);
	polygon.setPosition(sf::Vector2f(posx, posy));

	polygon.setOutlineThickness(OutlineThickness);
	polygon.setOutlineColor(OutlineColor);

	return polygon;
}