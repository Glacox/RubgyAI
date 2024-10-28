#pragma once
#include <vector>
#include "Ball.hpp"
#include "Field.hpp"
#include "Player.hpp"

namespace sf { class RenderWindow; }

class GameManager {
    std::vector<Entity*> mEntities;
    std::vector<Player*> mPlayers;
    sf::RenderWindow* mWindow;
    float mDeltaTime;
    Ball* mBall;
    Field* mField;
    sf::Vector2f mBallInitialPosition;

    GameManager();
    void addEntity(Entity* entity);

public:
    ~GameManager();

    static GameManager* Instantiate();
    static GameManager* Get();
    void Update();
    void Draw();

    void setWindow(sf::RenderWindow* window);
    void setDeltaTime(float deltaTime);
    float getDeltaTime() const;
    Ball* getBall() const { return mBall; }
    Field* getField() const { return mField; }
    const std::vector<Player*>& getPlayers() const { return mPlayers; }
    void resetPositions();

    friend Entity;
};