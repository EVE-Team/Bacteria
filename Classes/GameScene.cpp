#include "GameScene.h"
#include "PauseScene.h"
#include "Player.h"
#include "Planktons.h"
#include "Utils.h"
#include "Plankton.h"

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


	pause = Sprite::create("button_black_pause.png");
	pause->setPosition(Vec2(visibleSize) - Vec2(40, 40));
	pause->setScale(0.6);
	addChild(pause);

	player = Player::create();
	player->SetArea(10000);
	addChild(player);

	massText = Label::createWithTTF("Mass: " + std::to_string(player->GetArea()), "fonts/Marker Felt.ttf", 18);
	massText->setAnchorPoint(Vec2(0, 0.5));
	massText->setPosition(Vec2(40, visibleSize.height - 40));
	addChild(massText);

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

		{
			Vec2 plMov = location - player->getPosition();
			float dist = Utils::length(plMov);
			float mul = 100.0 / dist;
			plMov *= mul;
			player->SetVel(plMov);
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}

void GameScene::update(float dt)
{
	Layer::update(dt);

	player->Tick(dt);

	for (auto it = planktons->list.begin(); it != planktons->list.end(); ++it)
	{
		if (CircleSprite::Collide(player, *it))
		{
			player->SetArea(player->GetArea() + (*it)->GetArea());
			massText->setString("Mass: " + std::to_string(player->GetArea()));

			planktons->removeChild(*it, true);
			planktons->list.erase(it);

			break;
		}
	}
}

void GameScene::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void GameScene::onExit()
{
	unscheduleUpdate();
	Layer::onExit();
}
