#include "ScoreScene.h"
#include "HelloWorldScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ScoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2());
	addChild(background);

	{
		auto bg = Sprite::create("scores_bg.png");
		bg->setPosition(Vec2(Utils::GetVisibleSize().width / 2, Utils::GetVisibleSize().height / 2));
		addChild(bg);
	}

	std::string scoreText = "Scores:\n";
	auto scoreVector = Utils::GetHighScores();
	for (size_t i = 0; i < scoreVector.size(); ++i)
	{
		scoreText += Utils::to_string(i + 1) + ": " + Utils::to_string(scoreVector[i]) + "\n";
	}

	scores = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", 36);
	scores->setPosition(Vec2(Utils::GetVisibleSize().width / 2, Utils::GetVisibleSize().height / 2 + 50));
	addChild(scores);

	{
		auto btn = Sprite::create("button.png");
		btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 100));
		btn->setScaleX(1.2f);
		addChild(btn);
	}

	menu = Label::createWithTTF("Back to menu", "fonts/Marker Felt.ttf", 36);
	menu->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 100));
	addChild(menu);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (menu->getBoundingBox().containsPoint(location))
		{
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
