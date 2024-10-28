#pragma once
#include "libraries.h"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"


class Player;
class Ball;

class Action {
public:
    virtual void Start(Player* Player) = 0;
    virtual void Update(Player* Player) = 0;
    virtual void End(Player* Player) = 0;
};

class IdleAction : public Action {
public:
    virtual void Start(Player* Player) override {}
    virtual void Update(Player* Player) override {}
    virtual void End(Player* Player) override {}
};

class DefendingAction : public Action {
public:
    virtual void Start(Player* player) override
    {
        
    }

    virtual void Update(Player* player) override
    {
        //std::cout << "\rDefending";

        Ball* ball = GameManager::Get()->getBall();

        player->goToPosition(ball->getPosition());

        float ballDistance = Utils::GetDistance(player->getPosition(), ball->getPosition());
        const float catchDistance = 50.0f;

        if (ballDistance < catchDistance) {
            player->catchBall(ball);
        }
    }

    virtual void End(Player* player) override
    {
    }
};

class AttackingAction : public Action {
public:
    virtual void Start(Player* player) override 
    {
        
    }

    virtual void Update(Player* player) override 
    {
        std::cout << "\rAttacking";
        player->setColor(sf::Color::Magenta);
        Field* mField = new Field();
        if (player->getTeam() == Team::TeamA)
        {
            player->goToPosition(sf::Vector2f(mField->getRightTryLine(), player->getPosition().y));
        }
        
        if (player->getTeam() == Team::TeamB)
        {
            player->goToPosition(sf::Vector2f(mField->getLeftTryLine(), player->getPosition().y));
        }

        if (player->getPosition().x > 300)
        {
            player->setState(Context::State::Passing);
        }

        
    }

    virtual void End(Player* player) override {}
};

class PassingAction : public Action {
public:

    virtual void Start(Player* player) override 
    {
        
    }

    virtual void Update(Player* player) override 
    {
        std::cout << "\rPassing";
        player->setColor(sf::Color::Blue);
        Ball* ball = GameManager::Get()->getBall();
        int selectedPlayer;
        int playerArraySize = GameManager::Get()->getPlayers().size();

        player->releaseBall();
        selectedPlayer = rand() % playerArraySize + 0;

        if ((player->getTeam() == GameManager::Get()->getPlayers()[selectedPlayer]->getTeam()) ||
            (player->getTeam() == GameManager::Get()->getPlayers()[selectedPlayer]->getTeam())  )
        {
            ball->goToPosition(GameManager::Get()->getPlayers()[selectedPlayer]->getPosition());
        }

        else 
        {

        }

    }
    virtual void End(Player* player) override 
    {
    }

};

class FollowingAction : public Action {
public:
    virtual void Start(Player* player) override 
    {
        
    }

    virtual void Update(Player* player) override 
    {
        //std::cout << "\rFollowing";
        player->setColor(sf::Color::White);
        Field* mField = new Field();

        if (player->getTeam() == Team::TeamA)
        {
            player->goToPosition(sf::Vector2f(mField->getRightTryLine(), player->getPosition().y));
        }

        if (player->getTeam() == Team::TeamB)
        {
            player->goToPosition(sf::Vector2f(mField->getLeftTryLine(), player->getPosition().y));
        }
    }


    virtual void End(Player* player) override 
    {
    }
};
