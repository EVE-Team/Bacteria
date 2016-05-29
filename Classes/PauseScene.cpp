#include "PauseScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

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


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const float centerX = visibleSize.width / 2;


	auto labelNode = Label::createWithTTF(label, "fonts/Marker Felt.ttf", 24);
	labelNode->setAnchorPoint(Vec2(0, 0.5));
	labelNode->setPosition(Vec2(40, visibleSize.height - 40));
	addChild(labelNode);

	if (resumeAllowed)
	{
		resume = Sprite::create("Resume.png");
		resume->setPosition(Vec2(centerX, 300));
		addChild(resume);
	}

	restart = Sprite::create("Restart.png");
	restart->setPosition(Vec2(centerX, 200));
	addChild(restart);

	menu = Sprite::create("Exit.png");
	menu->setPosition(Vec2(centerX, 100));
	addChild(menu);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (resume && resume->boundingBox().containsPoint(location))
		{
			Director::getInstance()->popScene();
			return true;
		}

		if (restart->boundingBox().containsPoint(location))
		{
			Director::getInstance()->popScene();
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		if (menu->boundingBox().containsPoint(location))
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
