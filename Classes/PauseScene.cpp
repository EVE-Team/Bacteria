#include "PauseScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* PauseScene::createScene(std::string const& label, bool resumeAllowed)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create(label, resumeAllowed);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

PauseScene* PauseScene::create(std::string const& label, bool resumeAllowed)
{
	PauseScene *pRet = new(std::nothrow) PauseScene();
	if (pRet && pRet->init(label, resumeAllowed))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

// on "init" you need to initialize your instance
bool PauseScene::init(std::string const& label, bool resumeAllowed)
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

	auto labelNode = Sprite::create(label);
	if (resumeAllowed)
		labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 400));
	else
		labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 350));
	addChild(labelNode);

	if (resumeAllowed)
	{
		{
			auto btn = Sprite::create("button.png");
			btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 300));
			btn->setScaleX(1.2f);
			addChild(btn);
		}

		resume = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 36);
		resume->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 300));
		addChild(resume);
	}

	{
		auto btn = Sprite::create("button.png");
		btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 200));
		btn->setScaleX(1.2f);
		addChild(btn);
	}

	restart = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 36);
	restart->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 200));
	addChild(restart);

	{
		auto btn = Sprite::create("button.png");
		btn->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 100));
		btn->setScaleX(1.2f);
		addChild(btn);
	}

	menu = Label::createWithTTF("Main menu", "fonts/Marker Felt.ttf", 36);
	menu->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 100));
	addChild(menu);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (resume && resume->getBoundingBox().containsPoint(location))
		{
			Director::getInstance()->popScene();
			return true;
		}

		if (restart->getBoundingBox().containsPoint(location))
		{
			Director::getInstance()->popScene();
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		if (menu->getBoundingBox().containsPoint(location))
		{
			Director::getInstance()->popScene();
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
