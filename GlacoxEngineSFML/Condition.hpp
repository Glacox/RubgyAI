#pragma once
#include "Player.hpp"
#include "GameManager.hpp"
#include "Ball.hpp"
#include "Utils.hpp"
#include <iostream>

class Condition {
public:
    virtual bool Test(Player* Player) = 0;
};

class AttackCondition : public Condition {
public:
    virtual bool Test(Player* Player) override {
        if (Player->getPosition().x > 500) {
            std::cout << "AttackCondition: True" << std::endl;
            return true;
        }
        return false;
    }
};

class BallFreeCondition : public Condition {
public:
    virtual bool Test(Player* Player) override {
        Ball* ball = GameManager::Get()->getBall();
        bool result = ball && ball->isFree();
        if (result) {
            std::cout << "BallFreeCondition: True" << std::endl;
        }
        return result;
    }
};

class OpponentNearbyCondition : public Condition {
    const float OPPONENT_DETECTION_RANGE = 150.f;
public:
    virtual bool Test(Player* player) override {
        if (!player) return false;

        auto* gm = GameManager::Get();
        const auto& players = gm->getPlayers();

        for (const auto* other : players) {
            if (other == player) continue;
            if (other->getTeam() == player->getTeam()) continue;

            // Vérifie si l'adversaire est devant nous
            if (other->getPosition().x > player->getPosition().x) {
                float distance = Utils::GetDistance(player->getPosition(), other->getPosition());
                if (distance < OPPONENT_DETECTION_RANGE) {
                    std::cout << "OpponentNearbyCondition: Found opponent in front at distance " << distance << std::endl;
                    return true;
                }
            }
        }
        return false;
    }
};

class ShouldInterceptCondition : public Condition {
public:
    virtual bool Test(Player* player) override {
        if (!player) return false;

        Ball* ball = GameManager::Get()->getBall();
        Player* ballCarrier = ball->getHolder();

        if (ballCarrier && ballCarrier->getTeam() != player->getTeam()) {
            std::cout << "ShouldInterceptCondition: Enemy has ball" << std::endl;
            return true;
        }

        if (ball->isFree()) {
            std::cout << "ShouldInterceptCondition: Ball is free" << std::endl;
            return true;
        }

        return false;
    }
};

class ShouldFollowCondition : public Condition {
public:
    virtual bool Test(Player* player) override {
        if (!player) return false;

        Ball* ball = GameManager::Get()->getBall();
        Player* ballCarrier = ball->getHolder();

        if (ballCarrier && ballCarrier != player &&
            ballCarrier->getTeam() == player->getTeam()) {
            std::cout << "ShouldFollowCondition: Teammate has ball" << std::endl;
            return true;
        }
        return false;
    }
};