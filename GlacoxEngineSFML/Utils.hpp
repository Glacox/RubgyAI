#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace Utils {
    sf::Vector2f Vector2Normalize(const sf::Vector2f& vector);
    float GetDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);
}