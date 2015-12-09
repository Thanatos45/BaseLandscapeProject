#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"#
#include <sstream>

using namespace cocos2d;
using namespace std;

struct Projectile
{
	Sprite* sprite;
	bool onScreen;
	Point vector;
	int speed;
	int damage;
	Point temp;
	int radius;
};

struct PowerUp
{
	Sprite* sprite;
	bool onScreen;
	int counter;
	float effect;
	int radius;
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float);

	void updateBackground();

	void updateProjectile();

	//Deal with touches.
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

private:
	Sprite* _bg1;
	Sprite* _bg2;
	Sprite* _turret;
	PowerUp* _dmgPwrUp;
	Projectile* _projectile;
	Point _touchLocation;
	float _turretAngleRadians;
	Size winSize;
	static const int kScrollSpeed = 10;
};

#endif // __HELLOWORLD_SCENE_H__
