#include "GameManager.h"

//Set the instance to be null.
GameManager* GameManager::instance = NULL;

//-------------------------------------------------------------------------

GameManager* GameManager::sharedGameManager()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return instance;
}

//-------------------------------------------------------------------------

GameManager::GameManager()
{
	isGameLive = false;
}

//-------------------------------------------------------------------------

GameManager::~GameManager()
{

}

//-------------------------------------------------------------------------

void GameManager::AddToScore(int increment,int interval)
{
	interval = (int)Timer.
	this->score += increment * interval;
}

//-------------------------------------------------------------------------

void GameManager::ResetScore()
{
	score = 0;
}

//-------------------------------------------------------------------------

int GameManager::GetScore()
{
	return score;
}

//-------------------------------------------------------------------------
