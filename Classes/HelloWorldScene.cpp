#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ScoreScene.h"

USING_NS_CC;

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


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2());
	addChild(background);

	auto labelNode = Label::createWithTTF("Bacteria", "fonts/Marker Felt.ttf", 72);
	labelNode->setPosition(Vec2(visibleSize.width / 2, 400));
	addChild(labelNode);

	newGame = Label::createWithTTF("New game", "fonts/Marker Felt.ttf", 36);
	newGame->setPosition(Vec2(visibleSize.width / 2, 300));
	addChild(newGame);

	scores = Label::createWithTTF("Scores", "fonts/Marker Felt.ttf", 36);
	scores->setPosition(Vec2(visibleSize.width / 2, 200));
	addChild(scores);

	exit = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 36);
	exit->setPosition(Vec2(visibleSize.width / 2, 100));
	addChild(exit);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (newGame->boundingBox().containsPoint(location))
		{
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		if (scores->boundingBox().containsPoint(location))
		{
			auto scene = ScoreScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		if (exit->boundingBox().containsPoint(location))
		{
			Director::getInstance()->end();
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
