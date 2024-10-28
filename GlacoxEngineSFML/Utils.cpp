#include <SFML/System/Vector2.hpp>

#include <cmath>

#include "Utils.hpp"

namespace Utils {
    sf::Vector2f Vector2Normalize(const sf::Vector2f& vector) {
        float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        if (magnitude == 0) {
            return { 0, 0 };
        }
        return { vector.x / magnitude, vector.y / magnitude };
    }

    float GetDeltaTime()
    {
        return 0.016f;
    }

    float GetDistance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}

