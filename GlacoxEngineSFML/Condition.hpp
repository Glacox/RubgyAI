#pragma once
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"

class Condition {
public:
    virtual bool Test(Player* Player) = 0;

};

class AttackingCondition : public Condition {
public:
    virtual bool Test(Player* Player) override {
        if (Player->hasBall())
            return true;
    }
};

class DefendingCondition : public Condition {
public:
    virtual bool Test(Player* Player) override {

        if (!Player->hasBall()) {

            for (auto otherPlayer : GameManager::Get()->getPlayers())
            {
                if (otherPlayer->getTeam() == Player->getTeam()
                    && otherPlayer->hasBall())
                {
                    return false;
                }
            }

        return true;

        }

    }
};

class PassingCondition : public Condition {
public:
    virtual bool Test(Player* Player) override {
        return false;
    }
};

class FollowingCondition : public Condition {
public:
    virtual bool Test(Player* Player) override {

        if (!Player->hasBall()) {

            for (auto otherPlayer : GameManager::Get()->getPlayers())
            {
                if (otherPlayer->getTeam() == Player->getTeam()
                    && otherPlayer->hasBall())
                {
                    return true;
                }
            }

            return false;

        }

        return false;
    }
};