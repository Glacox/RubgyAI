#include "GameManager.hpp"
#include "Behaviour.hpp"
#include "Action.hpp"
#include "Transition.hpp"
#include "Player.hpp"
#include "Ball.hpp"

namespace {
    static GameManager* mInstance = nullptr;
}

GameManager::GameManager() {
    mField = new Field();

    Behaviour* behaviour = new Behaviour();

    // Actions
    Action* idle = new IdleAction();
    Action* attacking = new AttackingAction();
    Action* following = new FollowingAction();
    Action* defending = new DefendingAction();
    Action* passing = new PassingAction();

    // Configuration des actions pour chaque état
    behaviour->AddAction(Context::State::Idle, idle);
    behaviour->AddAction(Context::State::Attacking, attacking);
    behaviour->AddAction(Context::State::Following, following);
    behaviour->AddAction(Context::State::Defending, defending);
    behaviour->AddAction(Context::State::Passing, passing);

    // Transitions IDLE
    Transition* t_IdleToAttacking = new Transition();
    t_IdleToAttacking->setTargetState(Context::State::Attacking);
    t_IdleToAttacking->addCondition(new AttackingCondition());
    behaviour->AddTransition(Context::State::Idle, t_IdleToAttacking);

    Transition* t_IdleToFollowing = new Transition();
    t_IdleToFollowing->setTargetState(Context::State::Following);
    t_IdleToFollowing->addCondition(new FollowingCondition());
    behaviour->AddTransition(Context::State::Idle, t_IdleToFollowing);

    Transition* t_IdleToDefending = new Transition();
    t_IdleToDefending->setTargetState(Context::State::Defending);
    t_IdleToDefending->addCondition(new DefendingCondition());
    behaviour->AddTransition(Context::State::Idle, t_IdleToDefending);

    Transition* t_AttackingToPassing = new Transition();
    t_AttackingToPassing->setTargetState(Context::State::Passing);
    t_AttackingToPassing->addCondition(new PassingCondition());
    behaviour->AddTransition(Context::State::Attacking, t_AttackingToPassing);

    Transition* t_DefendingToAttacking = new Transition();
    t_DefendingToAttacking->setTargetState(Context::State::Attacking);
    t_DefendingToAttacking->addCondition(new AttackingCondition());
    behaviour->AddTransition(Context::State::Defending, t_DefendingToAttacking);

    // Création des joueurs
    float startXA = mField->getLeftTryLine() + 50.f;
    Player* a1 = new Player(sf::Vector2f(startXA, 360.f), behaviour, Team::TeamA);
    Player* a2 = new Player(sf::Vector2f(startXA-50 , 300.f), behaviour, Team::TeamA);
    Player* a3 = new Player(sf::Vector2f(startXA - 50, 420.f), behaviour, Team::TeamA);

    float startXB = mField->getRightTryLine() - 10.f;
    //Player* b1 = new Player(sf::Vector2f(startXB, 360.f), behaviour, Team::TeamB);
    //Player* b2 = new Player(sf::Vector2f(startXB+50, 420.f), behaviour, Team::TeamB);

    mPlayers.push_back(a1);
    mPlayers.push_back(a2);
    mPlayers.push_back(a3);
    //mPlayers.push_back(b1);
    //mPlayers.push_back(b2);

    for (auto* p : mPlayers) {
        mEntities.push_back(p);
    }

    mBallInitialPosition = sf::Vector2f(mField->getWidth() / 2, mField->getHeight() / 2);
    mBall = new Ball(mBallInitialPosition);
    mEntities.push_back(mBall);
    //mPlayers[rand() % mPlayers.size() + 0]->catchBall(mBall);
    a1->catchBall(mBall);

    // Initialisation des états
    a1->setState(Context::State::Idle);
    a2->setState(Context::State::Idle);
    a3->setState(Context::State::Idle);
    //b1->setState(Context::State::Idle);
    //b2->setState(Context::State::Idle);

    // Démarrage des comportements
    behaviour->Start(a1);
    behaviour->Start(a2);
    behaviour->Start(a3);
    //behaviour->Start(b1);
    //behaviour->Start(b2);

    if (a1->getPosition().x > 300)
    {
        a1->setState(Context::State::Passing)
    }
}

GameManager::~GameManager() {
    delete mField;
    for (auto entity : mEntities) {
        delete entity;
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

    if (mBall->getPosition().x > mField->getRightTryLine() || mBall->getPosition().x < mField->getLeftTryLine()) 
    {
        resetPositions();
    }
}

void GameManager::Draw()
{
    mField->Draw(mWindow);
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

void GameManager::resetPositions() {
    std::cout << "Resetting positions after try" << std::endl;
    // Reset tous les joueurs
    for (auto* player : mPlayers) {
        player->resetToInitialPosition();
        player->setColor(player->getInitialColor());
    }

    // Reset la balle
    mBall->setPosition(mBallInitialPosition);
    mBall->setDirection(sf::Vector2f(0, 0));
    if (mBall->getHolder()) {
        mBall->getHolder()->releaseBall();
    }

    mPlayers[rand() % mPlayers.size() + 0]->catchBall(mBall);

}