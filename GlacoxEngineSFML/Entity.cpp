#include "Entity.hpp"

#include "GameManager.hpp"
#include "Utils.hpp"

#include <SFML/Graphics/Shape.hpp>

Entity::Entity()
{ 
}

Entity::~Entity()
{ 
}

void Entity::Update() {
    float dt = GameManager::Get()->getDeltaTime();
    sf::Vector2f newPosition = mShape->getPosition();
    newPosition += dt * mSpeed * mDirection;
    mShape->setPosition(newPosition);
}

void Entity::setPosition(const sf::Vector2f& position)
{
    mShape->setPosition(position);
}

const sf::Vector2f& Entity::getPosition() const
{
    return mShape->getPosition();
}

void Entity::setDirection(const sf::Vector2f& new_direction)
{
    mDirection = new_direction;
}

void Entity::goToPosition(const sf::Vector2f& position)
{
    setDirection(Utils::Vector2Normalize(position - getPosition()));
}

const sf::Shape& Entity::getShape()
{
    return *mShape;
}
