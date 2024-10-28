#pragma once
#include <SFML/Graphics.hpp>

class Field {
public:
    Field(float width = 1280.f, float height = 720.f);
    void Draw(sf::RenderWindow* window);

    float getLeftTryLine() const { return mLeftTryLine; }
    float getRightTryLine() const { return mRightTryLine; }
    float getWidth() const { return mWidth; }
    float getHeight() const { return mHeight; }

private:
    float mWidth;
    float mHeight;
    float mLeftTryLine;
    float mRightTryLine;

    sf::RectangleShape mLeftLine;
    sf::RectangleShape mRightLine;
};