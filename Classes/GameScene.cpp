#include "GameScene.h"
#include "PauseScene.h"
#include "Player.h"
#include "Planktons.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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


	pause = Sprite::create("button_black_pause.png");
	pause->setPosition(Vec2(centerX, 100));
	addChild(pause);

	player = Player::create();
	player->SetArea(10000);
	addChild(player);

	planktons = Planktons::create();
	addChild(planktons);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (pause->boundingBox().containsPoint(location))
		{
			auto scene = PauseScene::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
