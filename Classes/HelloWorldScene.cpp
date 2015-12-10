#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	_turret = (Sprite*)rootNode->getChildByName("PlayerTurret");

	_projectile = new Projectile();

	_projectile->sprite = (Sprite*)rootNode->getChildByName("Projectile");

	_projectile->speed = 15;

	_projectile->onScreen = false;

	_projectile->radius =_projectile->sprite->getContentSize().width / 2;

	winSize = Director::sharedDirector()->getWinSize();

	//DmgPwrUp - need to move to own method
	_dmgPwrUp = new PowerUp();

	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("res/Damage.plist");

	_dmgPwrUp->sprite = Sprite::create();

	// load all the animation frames into an array
	Vector<SpriteFrame*> frames;
	for (int i = 1; i <= 2; i++)
	{
		stringstream ss;
		ss << "Damage_" << i << ".png";
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
	}

	// play the animation
	Animation* anim = Animation::createWithSpriteFrames(frames, 0.1f);
	_dmgPwrUp->sprite->runAction(RepeatForever::create(Animate::create(anim)));
	_dmgPwrUp->sprite->setPosition(100, 100);
	_dmgPwrUp->sprite->setScale(0.5);
	_dmgPwrUp->onScreen = false;

	this->addChild(_dmgPwrUp->sprite);

	//TOUCHES
	//Set up a touch listener.
	auto touchListener = EventListenerTouchOneByOne::create();

	//Set callbacks for our touch functions.
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	//Add our touch listener to event listener list.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//background stuff
	_bg1 = (Sprite*)rootNode->getChildByName("Stars1");
	_bg2 = (Sprite*)rootNode->getChildByName("Stars2");

	_bg1->setAnchorPoint(Point(0, 0));
	_bg1->setPosition(Point(0, 0));

	_bg2->setAnchorPoint(Point(0, 0));
	_bg2->setPosition(Point(_bg1->boundingBox().size.width - 1, 0));

	_scrollSpeed = 10;

	this->scheduleUpdate();

    return true;
}
//
void HelloWorld::update(float delta)
{
	updateBackground();

	//Maybe we should add a scale variable to some of the structs - that's what the last divide by 2 is for below
	_dmgPwrUp->radius = (_dmgPwrUp->sprite->getContentSize().width / 2) / 2; //Need to figure out how to fix this

	if (_projectile->sprite->getBoundingBox().intersectsCircle(_dmgPwrUp->sprite->getPosition(), _dmgPwrUp->radius)) //Need to move to own method
	{
		_dmgPwrUp->sprite->setPositionX(-100);
		_projectile->sprite->setPositionY(-100);
		//Add code to boost damage - when enemies are in the game.
	}
	
	if (_projectile->onScreen)
	{
		updateProjectile();
	}
}

void HelloWorld::updateBackground()
{
	Point bg1Pos = _bg1->getPosition();
	Point bg2Pos = _bg2->getPosition();
	bg1Pos.x -= _scrollSpeed;
	bg2Pos.x -= _scrollSpeed;

	// move scrolling background back by one screen width to achieve "endless" scrolling
	if (bg1Pos.x < -(_bg1->getContentSize().width))
	{
		bg1Pos.x += _bg1->getContentSize().width;
		bg2Pos.x += _bg2->getContentSize().width;
	}

	// remove any inaccuracies by assigning only int values 
	// (prevents floating point rounding errors accumulating over time)
	bg1Pos.x = (int)bg1Pos.x;
	bg2Pos.x = (int)bg2Pos.x;
	_bg1->setPosition(bg1Pos);
	_bg2->setPosition(bg2Pos);
}

void HelloWorld::updateProjectile()
{	
	//checks if projectile is on screen
	if (_projectile->sprite->getPositionX() > winSize.width + _projectile->sprite->getContentSize().width || 
		_projectile->sprite->getPositionX() < 0 - _projectile->sprite->getContentSize().width ||
		_projectile->sprite->getPositionY() > winSize.height + _projectile->sprite->getContentSize().height ||
		_projectile->sprite->getPositionY() < 0 - _projectile->sprite->getContentSize().height)
	{
		_projectile->onScreen = false;
	}
	else
	{
		_projectile->onScreen = true;
		_projectile->temp.x += _projectile->vector.x * _projectile->speed;
		_projectile->temp.y += _projectile->vector.y * _projectile->speed;
		_projectile->sprite->setPosition(_projectile->temp.x, _projectile->temp.y);
	}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	_touchLocation = touch->getLocation();

	//ccpsub gets angle between them
	_turretAngleRadians = ccpToAngle(ccpSub(_turret->getPosition(), _touchLocation));

	_turret->setRotation(180 - CC_RADIANS_TO_DEGREES(_turretAngleRadians));

	if (!_projectile->onScreen)
	{
		_projectile->vector = Point(-cos(_turretAngleRadians), -sin(_turretAngleRadians));

		_projectile->sprite->setPosition(_turret->getPosition().x, _turret->getPosition().y);
		_projectile->temp.setPoint(_turret->getPosition().x, _turret->getPosition().y);
	}

	_projectile->onScreen = true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

