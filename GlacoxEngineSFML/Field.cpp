#include "Field.hpp"

Field::Field(float width, float height) :
    mWidth(width),
    mHeight(height)
{
    // Les lignes sont � 10% et 90% du terrain
    mLeftTryLine = mWidth * 0.1f;
    mRightTryLine = mWidth * 0.9f;

    // Cr�ation des lignes visuelles
    mLeftLine.setSize(sf::Vector2f(5.f, mHeight));
    mRightLine.setSize(sf::Vector2f(5.f, mHeight));

    mLeftLine.setPosition(mLeftTryLine, 0);
    mRightLine.setPosition(mRightTryLine, 0);

    mLeftLine.setFillColor(sf::Color::White);
    mRightLine.setFillColor(sf::Color::White);
}

void Field::Draw(sf::RenderWindow* window) {
    window->draw(mLeftLine);
    window->draw(mRightLine);
}