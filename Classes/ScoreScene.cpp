#include "ScoreScene.h"
#include "MenuScene.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
	return Utils::CreateScene<ScoreScene>();
}

ScoreScene* ScoreScene::create()
{
	return Utils::CreateCocosObject<ScoreScene>(
		[](){ return new (std::nothrow) ScoreScene(); },
		[](ScoreScene *s){ return s->init(); });
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
	scores->setPosition(Vec2(Utils::GetVisibleSize().width / 2, Utils::GetVisibleSize().height / 2 + 25));
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
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX316.mp3");
			auto scene = MenuScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
