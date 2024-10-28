#pragma once
#include "Entity.hpp"
#include "libraries.h"

class Player; 

class Ball : public Entity {
public:
    Ball(const sf::Vector2f& position);
    ~Ball();

    void Update() override;
    void setHolder(Player* player) { mHolder = player; }
    Player* getHolder() const { return mHolder; }
    bool isFree() const { return mHolder == nullptr; }

private:
    Player* mHolder = nullptr;
};