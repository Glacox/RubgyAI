#include "GameManager.hpp"

#include "Behaviour.hpp"
#include "Action.hpp"
#include "Transition.hpp"

#include "Player.hpp"
#include "Ball.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <iostream>

namespace 
{
static GameManager* mInstance = nullptr;
}

GameManager::GameManager()
{
    Behaviour * behaviour = new Behaviour();
	Transition* transition = new Transition();

	// init behaviour here:
	// example code:
	Action* move = new Move;
	Action* attacking = new AttackingAction;

	behaviour->AddAction(Context::State::Moving, move);
	behaviour->AddAction(Context::State::Attacking, attacking);

	
	transition->setTargetState(Context::State::Attacking);
	transition->addCondition(new AttackCondition());
	behaviour->AddTransition(Context::State::Moving, transition);

    Player * p1 = new Player(sf::Vector2f(100, 360), behaviour);
    Player * p2 = new Player(sf::Vector2f(1180, 360), behaviour);
    mEntities.push_back(p1);

    Ball * ball = new Ball(sf::Vector2f(640, 360));
	mEntities.push_back(ball);

	p1->setState(Context::State::Moving);
	behaviour->Start(p1);
}

GameManager::~GameManager()
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		delete mEntities[i];
	}
}

GameManager* GameManager::Instantiate()
{
	if (!mInstance)
    {
        mInstance = new GameManager();
        return mInstance;
    }
    return nullptr;
}

GameManager* GameManager::Get()
{
	return mInstance;
}

void GameManager::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

void GameManager::Update()
{
	for (Entity* entity : mEntities)
	{
		entity->Update();
		
	}
}

void GameManager::Draw()
{
	for (Entity* entity : mEntities)
	{
		mWindow->draw(entity->getShape());
	}
}

void GameManager::setDeltaTime(float deltaTime)
{
	mDeltaTime = deltaTime;
}

float GameManager::getDeltaTime() const
{
	return mDeltaTime;
}

void GameManager::addEntity(Entity* entity)
{
	mEntities.push_back(entity);
}
