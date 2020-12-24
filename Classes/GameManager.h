#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>

//-------------------------------------------------------------------------

class GameManager
{

	//-------------------------------------------------------------------------
public:
	~GameManager();
	static GameManager* sharedGameManager();

	//Score accessors.
	void AddToScore(int increment,int interval);
	void ResetScore();
	int  GetScore();

	//Accessible variable
	bool isGameLive;

	//-------------------------------------------------------------------------
private:
	GameManager();
	static GameManager* instance;
	int  score;
};

//-------------------------------------------------------------------------
#endif /* GameManager_h */
