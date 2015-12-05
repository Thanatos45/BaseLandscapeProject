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

	this->scheduleUpdate();

    return true;
}
//
void HelloWorld::update(float delta)
{
	Point bg1Pos = _bg1->getPosition();
	Point bg2Pos = _bg2->getPosition();
	bg1Pos.x -= kScrollSpeed;
	bg2Pos.x -= kScrollSpeed;

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

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Point location = touch->getLocation();

	//ccpsub gets angle between them
	float angleRadians = ccpToAngle(ccpSub( _turret->getPosition(), location));

	_turret->setRotation(180 - CC_RADIANS_TO_DEGREES(angleRadians));
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

