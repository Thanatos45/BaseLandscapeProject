#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

struct Projectile
{
	Sprite* projectileSprite;
	bool onScreen;
	Point vector;
	int speed;
	int damage;
	Point temp;
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
	Projectile* _projectile;
	Point touchLoc;
	float angleRadians;
	Size winSize;
	static const int kScrollSpeed = 15;
};

#endif // __HELLOWORLD_SCENE_H__
