#include "GameManager.hpp"
#include "Behaviour.hpp"
#include "Action.hpp"
#include "Transition.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace {
    static GameManager* mInstance = nullptr;
}

GameManager::GameManager() {
    mField = new Field();

    Behaviour* behaviour = new Behaviour();

    // Actions
    Action* move = new Move();
    Action* attacking = new AttackingAction();
    Action* catchBall = new CatchBallAction();
    Action* hasBall = new HasBallAction();
    Action* pass = new PassAction();
    Action* intercept = new InterceptAction();
    Action* follow = new FollowAction();

    // Configuration des actions pour chaque état
    behaviour->AddAction(Context::State::Moving, move);
    behaviour->AddAction(Context::State::Attacking, attacking);
    behaviour->AddAction(Context::State::ChasingBall, catchBall);
    behaviour->AddAction(Context::State::HasBall, hasBall);
    behaviour->AddAction(Context::State::PassingBall, pass);
    behaviour->AddAction(Context::State::Intercepting, intercept);
    behaviour->AddAction(Context::State::Following, follow);

    // Transitions
    Transition* transitionToAttack = new Transition();
    transitionToAttack->setTargetState(Context::State::Attacking);
    transitionToAttack->addCondition(new AttackCondition());
    behaviour->AddTransition(Context::State::Moving, transitionToAttack);

    Transition* transitionToChaseBall = new Transition();
    transitionToChaseBall->setTargetState(Context::State::ChasingBall);
    transitionToChaseBall->addCondition(new BallFreeCondition());
    behaviour->AddTransition(Context::State::Moving, transitionToChaseBall);

    // Pour récupérer une balle libre même depuis HasBall
    Transition* transitionToChaseBallFromHasBall = new Transition();
    transitionToChaseBallFromHasBall->setTargetState(Context::State::ChasingBall);
    transitionToChaseBallFromHasBall->addCondition(new BallFreeCondition());
    behaviour->AddTransition(Context::State::HasBall, transitionToChaseBallFromHasBall);

    Transition* transitionToPass = new Transition();
    transitionToPass->setTargetState(Context::State::PassingBall);
    transitionToPass->addCondition(new OpponentNearbyCondition());
    behaviour->AddTransition(Context::State::HasBall, transitionToPass);

    Transition* transitionToIntercept = new Transition();
    transitionToIntercept->setTargetState(Context::State::Intercepting);
    transitionToIntercept->addCondition(new ShouldInterceptCondition());
    behaviour->AddTransition(Context::State::Moving, transitionToIntercept);

    Transition* transitionToFollow = new Transition();
    transitionToFollow->setTargetState(Context::State::Following);
    transitionToFollow->addCondition(new ShouldFollowCondition());
    behaviour->AddTransition(Context::State::Moving, transitionToFollow);

    // Création des joueurs
    float startXA = mField->getLeftTryLine() + 50.f;
    Player* p1 = new Player(sf::Vector2f(startXA, 360.f), behaviour, Team::TeamA);
    Player* p2 = new Player(sf::Vector2f(startXA - 100.f, 260.f), behaviour, Team::TeamA);

    float startXB = mField->getRightTryLine() - 50.f;
    Player* opponent = new Player(sf::Vector2f(startXB, 360.f), behaviour, Team::TeamB);

    mPlayers.push_back(p1);
    mPlayers.push_back(p2);
    mPlayers.push_back(opponent);

    for (auto* p : mPlayers) {
        mEntities.push_back(p);
    }

    mBallInitialPosition = sf::Vector2f(mField->getWidth() / 2, mField->getHeight() / 2);
    mBall = new Ball(mBallInitialPosition);
    mEntities.push_back(mBall);

    // Initialisation des états
    p1->setState(Context::State::Moving);
    p2->setState(Context::State::Moving);
    opponent->setState(Context::State::Moving);

    // Démarrage des comportements
    behaviour->Start(p1);
    behaviour->Start(p2);
    behaviour->Start(opponent);
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
    }

    // Reset la balle
    mBall->setPosition(mBallInitialPosition);
    mBall->setDirection(sf::Vector2f(0, 0));
    if (mBall->getHolder()) {
        mBall->getHolder()->releaseBall();
    }
}