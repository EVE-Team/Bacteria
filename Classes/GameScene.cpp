#include "GameScene.h"
#include "PauseScene.h"
#include "Player.h"
#include "Planktons.h"
#include "Utils.h"
#include "Plankton.h"
#include "Enemies.h"
#include "Enemy.h"
#include "HelloWorldScene.h"

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


	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	node = Node::create();
	node->setAnchorPoint(Vec2());
	addChild(node);

	auto background = Sprite::create("brushwalker137.png");
	Texture2D::TexParams tp;
	tp.minFilter = GL_LINEAR;
	tp.magFilter = GL_LINEAR;
	tp.wrapS = GL_REPEAT;
	tp.wrapT = GL_REPEAT;
	background->getTexture()->setTexParameters(tp);
	background->setTextureRect(Rect(Vec2(), Utils::fieldSize));
	background->setAnchorPoint(Vec2());
	node->addChild(background);

	planktons = Planktons::create();
	node->addChild(planktons);

	enemies = Enemies::create();
	node->addChild(enemies);

	player = Player::create();
	player->SetArea(5000);
	node->addChild(player);

	massText = Label::createWithTTF("Mass: " + std::to_string(player->GetArea()), "fonts/Marker Felt.ttf", 24);
	massText->setColor(Color3B(0, 0, 0));
	massText->setAnchorPoint(Vec2(0, 0.5));
	massText->setPosition(Vec2(40, visibleSize.height - 40));
	addChild(massText);

	pause = Sprite::create("button_black_pause.png");
	pause->setPosition(Vec2(visibleSize) - Vec2(40, 40));
	pause->setScale(0.6);
	addChild(pause);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (pause->boundingBox().containsPoint(location))
		{
			auto scene = PauseScene::createScene();
			Director::getInstance()->pushScene(scene);
			return true;
		}

		if (player->GetArea() >= 2 * Utils::planktonArea)
		{
			auto nodeLocation = location - node->getPosition();
			Vec2 plMov = nodeLocation - player->getPosition();
			float dist = Utils::length(plMov);
			float mul = 1500000.0 / dist;
			plMov *= mul;
			player->Push(plMov);

			player->SetArea(player->GetArea() - Utils::planktonArea);
			massText->setString("Mass: " + std::to_string(player->GetArea()));
			planktons->AddPlankton(player->getPosition());
			planktons->list.back()->Push(plMov * -0.05);
		}
		else
		{
			GameOver("You've lost too much mass");
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}

void GameScene::EatPlankton()
{
	for (auto it = planktons->list.begin(); it != planktons->list.end(); ++it)
	{
		if (!(*it)->Vulnerable())
			continue;

		if (Utils::length(player->getPosition() - (*it)->getPosition()) < player->GetRadius())
		{
			player->SetArea(player->GetArea() + (*it)->GetArea());
			massText->setString("Mass: " + std::to_string(player->GetArea()));

			planktons->removeChild(*it, true);
			planktons->list.erase(it);

			return;
		}
		else
		{
			for (auto enemy : enemies->list)
			{
				if (Utils::length(enemy->getPosition() - (*it)->getPosition()) < enemy->GetRadius())
				{
					enemy->SetArea(enemy->GetArea() + (*it)->GetArea());

					planktons->removeChild(*it, true);
					planktons->list.erase(it);

					return;
				}
			}
		}
	}
}

void GameScene::EnemyPlayerCollision()
{
	for (auto it = enemies->list.begin(); it != enemies->list.end(); ++it)
	{
		float dist = Utils::length(player->getPosition() - (*it)->getPosition());

		if (dist < player->GetRadius())
		{
			player->SetArea(player->GetArea() + (*it)->GetArea());
			massText->setString("Mass: " + std::to_string(player->GetArea()));

			enemies->removeChild(*it, true);
			enemies->list.erase(it);

			return;
		}
		else if (dist < (*it)->GetRadius())
		{
			GameOver("You've been eaten");
		}
	}
}

void GameScene::update(float dt)
{
	Layer::update(dt);

	player->Tick(dt);
	planktons->Tick(dt);

	EatPlankton();
	EnemyPlayerCollision();

	{
		Rect camRect(
			Vec2(player->getPosition().x - visibleSize.width / 2, player->getPosition().y - visibleSize.height / 2),
			visibleSize
		);

		if (camRect.getMinX() < 0)
			camRect.origin.x = 0;
		else if (camRect.getMaxX() > Utils::fieldSize.width)
			camRect.origin.x -= (camRect.getMaxX() - Utils::fieldSize.width);

		if (camRect.getMinY() < 0)
			camRect.origin.y = 0;
		else if (camRect.getMaxY() > Utils::fieldSize.height)
			camRect.origin.y -= (camRect.getMaxY() - Utils::fieldSize.height);

		node->setPosition(camRect.origin * -1);
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

void GameScene::GameOver(std::string const& reason)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}
