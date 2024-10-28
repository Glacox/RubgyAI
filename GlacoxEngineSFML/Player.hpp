#pragma once
#include "Entity.hpp"
#include "Context.hpp"
#include "Ball.hpp"

enum class Team {
    TeamA,
    TeamB
};

class Behaviour;

class Player : public Entity {
    Context::State mState;
    Behaviour* mBehaviour;
    Ball* mHeldBall;
    Team mTeam;
    sf::Vector2f mInitialPosition;

public:
    Player(const sf::Vector2f& position, Behaviour* behaviour, Team team);
    ~Player();

    void Update() override;
    Context::State getState() const;
    void setState(Context::State state);

    void catchBall(Ball* ball);
    void releaseBall();
    bool hasBall() const { return mHeldBall != nullptr; }
    Ball* getHeldBall() const { return mHeldBall; }
    Team getTeam() const { return mTeam; }

    void resetToInitialPosition();
    const sf::Vector2f& getInitialPosition() const { return mInitialPosition; }
};