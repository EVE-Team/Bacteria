#include "MenuScene.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return Utils::CreateScene<MenuScene>();
}

MenuScene* MenuScene::create()
{
	return Utils::CreateCocosObject<MenuScene>(
		[](){ return new (std::nothrow) MenuScene(); },
		[](MenuScene *s){ return s->init(); });
}

// on "init" you need to initialize your instance
bool MenuScene::init()
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
