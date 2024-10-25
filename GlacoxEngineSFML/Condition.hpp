#pragma once
#include "Player.hpp"
class Playground;
class Player;

class Condition 
{
public:
    virtual bool Test(Player * Player) = 0;
};

class AttackCondition : public Condition 
{
public:
    virtual bool Test(Player* Player) override
    {
        if (Player->getPosition().x > 500)
        {
            return true;
        }
    }
};