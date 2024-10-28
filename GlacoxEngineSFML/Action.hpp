#pragma once
#include "libraries.h"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <iostream>
#include <limits>

class Player;
class Ball;

class Action {
public:
    virtual void Start(Player* Player) = 0;
    virtual void Update(Player* Player) = 0;
    virtual void End(Player* Player) = 0;
};

class Move : public Action {
public:
    virtual void Start(Player* Player) override {
        Player->setDirection(sf::Vector2f(10, 0));
    }
    virtual void Update(Player* Player) override {}
    virtual void End(Player* Player) override {}
};

class AttackingAction : public Action {
public:
    virtual void Start(Player* Player) override {}
    virtual void Update(Player* Player) override {}
    virtual void End(Player* Player) override {}
};

class CatchBallAction : public Action {
public:
    virtual void Start(Player* player) override {
        if (!player) return;
        player->setSpeed(400.f);
    }

    virtual void Update(Player* player) override {
        if (!player) return;
        Ball* ball = GameManager::Get()->getBall();
        if (!ball || !ball->isFree()) {
            return;
        }

        // Calcul de la direction vers la balle
        sf::Vector2f toBall = ball->getPosition() - player->getPosition();
        float distance = std::sqrt(toBall.x * toBall.x + toBall.y * toBall.y);

        const float catchDistance = 50.0f;

        if (distance < catchDistance) {
            // Si on est assez proche, on attrape la balle
            player->catchBall(ball);
            if (player->hasBall()) {
                player->setState(Context::State::HasBall);
                std::cout << "Ball caught!" << std::endl;
            }
        }
        else {
            // Sinon on se dirige vers la balle
            player->setDirection(sf::Vector2f(toBall.x / distance, toBall.y / distance));
        }
    }

    virtual void End(Player* player) override {
        player->setDirection(sf::Vector2f(0, 0));
    }
};

class HasBallAction : public Action {
public:
    virtual void Start(Player* player) override {
        if (!player) return;
        player->setDirection(sf::Vector2f(1.0f, 0.0f));
        player->setSpeed(300.f);
        std::cout << "HasBallAction: Started running toward try line" << std::endl;
    }

    virtual void Update(Player* player) override {
        if (!player || !player->hasBall()) return;

        sf::Vector2f currentPos = player->getPosition();
        float tryLine = GameManager::Get()->getField()->getRightTryLine();

        // Continue d'avancer vers la ligne d'essai
        player->setDirection(sf::Vector2f(1.0f, 0.0f));

        if (currentPos.x >= tryLine) {
            std::cout << "HasBallAction: Try scored!" << std::endl;
            // Reset les positions
            GameManager::Get()->resetPositions();
        }
    }

    virtual void End(Player* player) override {}
};


class PassAction : public Action {
public:
    virtual void Start(Player* player) override {
        if (!player || !player->hasBall()) return;

        std::cout << "PassAction: Looking for teammate to pass to" << std::endl;
        Player* teammate = findBackwardTeammate(player);
        if (teammate) {
            std::cout << "PassAction: Found teammate for pass at position " << teammate->getPosition().x << std::endl;
            makeBallPass(player, teammate);
        }
        else {
            std::cout << "PassAction: No teammate found, keeping ball" << std::endl;
            player->setState(Context::State::HasBall);
        }
    }

    virtual void Update(Player* player) override {}
    virtual void End(Player* player) override {}

private:
    Player* findBackwardTeammate(Player* passer) {
        auto* gm = GameManager::Get();
        const auto& players = gm->getPlayers();
        Player* bestTeammate = nullptr;
        float bestScore = std::numeric_limits<float>::infinity();

        for (auto* other : players) {
            if (other == passer) continue;
            if (other->getTeam() != passer->getTeam()) continue;

            if (other->getPosition().x < passer->getPosition().x) {
                float distance = Utils::GetDistance(passer->getPosition(), other->getPosition());
                if (distance < bestScore) {
                    bestScore = distance;
                    bestTeammate = other;
                }
            }
        }
        return bestTeammate;
    }

    void makeBallPass(Player* passer, Player* receiver) {
        if (!passer || !receiver || !passer->hasBall()) return;

        Ball* ball = passer->getHeldBall();
        passer->releaseBall();

        sf::Vector2f direction = Utils::Vector2Normalize(
            receiver->getPosition() - passer->getPosition()
        );
        ball->setDirection(direction);
        ball->setSpeed(500.f);

        std::cout << "PassAction: Ball passed toward " << receiver->getPosition().x << std::endl;
        passer->setState(Context::State::Moving);
    }
};

class InterceptAction : public Action {
public:
    virtual void Start(Player* player) override {
        if (!player) return;
        player->setSpeed(400.f);
        std::cout << "InterceptAction: Started intercepting" << std::endl;
    }

    virtual void Update(Player* player) override {
        if (!player) return;

        Ball* ball = GameManager::Get()->getBall();
        if (!ball) return;

        // Si la balle est libre
        if (ball->isFree()) {
            const float catchDistance = 50.0f;
            float distance = Utils::GetDistance(player->getPosition(), ball->getPosition());

            if (distance < catchDistance) {
                player->catchBall(ball);
                if (player->hasBall()) {
                    player->setState(Context::State::HasBall);
                    std::cout << "Ball intercepted and caught!" << std::endl;
                }
            }
            else {
                sf::Vector2f toBall = ball->getPosition() - player->getPosition();
                player->setDirection(Utils::Vector2Normalize(toBall));
            }
        }
        // Si un adversaire a la balle
        else if (ball->getHolder() && ball->getHolder()->getTeam() != player->getTeam()) {
            player->goToPosition(ball->getHolder()->getPosition());
        }
    }

    virtual void End(Player* player) override {
        player->setDirection(sf::Vector2f(0, 0));
    }
};

class FollowAction : public Action {
public:
    virtual void Start(Player* player) override {
        if (!player) return;
        player->setSpeed(350.f);
        std::cout << "FollowAction: Started following" << std::endl;
    }

    virtual void Update(Player* player) override {
        if (!player) return;

        Ball* ball = GameManager::Get()->getBall();
        Player* ballCarrier = ball->getHolder();

        if (!ballCarrier || ballCarrier == player) return;

        if (ballCarrier->getTeam() == player->getTeam()) {
            sf::Vector2f targetPos = ballCarrier->getPosition();
            targetPos.x -= 100.f;

            player->goToPosition(targetPos);
            std::cout << "FollowAction: Following ball carrier at distance" << std::endl;
        }
    }

    virtual void End(Player* player) override {}
};