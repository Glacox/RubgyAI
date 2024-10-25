#pragma once
#include "libraries.h"
#include "Player.hpp"

class Player;
class Ball;

class Action
{
public:
    virtual void Start(Player * Player) = 0;
    virtual void Update(Player * Player) = 0;
    virtual void End(Player * Player) = 0;
};

class Move : public Action
{
public:
    virtual void Start(Player* Player) override 
    {
        Player->setDirection(sf::Vector2f(10, 0));
    }
    virtual void Update(Player* Player) override 
    {
    }
    virtual void End(Player* Player)override 
    {

    }
};

class AttackingAction : public Action
{
public:
    virtual void Start(Player* Player) override
    {
        
    }
    virtual void Update(Player* Player) override
    {
        Player->setDirection(sf::Vector2f(-10, 0));
    }
    virtual void End(Player* Player)override
    {

    }
};