#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

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


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2());
	addChild(background);

	{
		auto label = Sprite::create("title.png");
		label->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 400));
		addChild(label);
	}

	{
		auto btn = Sprite::create("button.png");
		btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 300));
		btn->setScaleX(1.2f);
		addChild(btn);
	}

	newGame = Label::createWithTTF("New game", "fonts/Marker Felt.ttf", 36);
	newGame->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 300));
	addChild(newGame);

	{
		auto btn = Sprite::create("button.png");
		btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 200));
		btn->setScaleX(1.2f);
		addChild(btn);
	}

	scores = Label::createWithTTF("Scores", "fonts/Marker Felt.ttf", 36);
	scores->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 200));
	addChild(scores);

	{
		auto btn = Sprite::create("button.png");
		btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 100));
		btn->setScaleX(1.2f);
		addChild(btn);
	}

	exit = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 36);
	exit->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 100));
	addChild(exit);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (newGame->getBoundingBox().containsPoint(location))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX316.mp3");
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		if (scores->getBoundingBox().containsPoint(location))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX316.mp3");
			auto scene = ScoreScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		if (exit->getBoundingBox().containsPoint(location))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX316.mp3");
			Director::getInstance()->end();
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
