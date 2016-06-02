#include "GameScene.h"
#include "PauseScene.h"
#include "Player.h"
#include "Planktons.h"
#include "Utils.h"
#include "Plankton.h"
#include "Enemies.h"
#include "Enemy.h"

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

	planktons = Planktons::create(this);
	node->addChild(planktons);

	enemies = Enemies::create(this);
	node->addChild(enemies);

	player = Player::create();
	player->SetArea(5000);
	player->setPosition(Vec2(Utils::fieldSize) / 2);
	node->addChild(player);

	massText = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	massText->setAnchorPoint(Vec2(0, 0.5));
	massText->setPosition(Vec2(40, Utils::GetVisibleSize().height - 40));
	UpdateInfo();
	addChild(massText);

	pause = Sprite::create("button_black_pause.png");
	pause->setPosition(Vec2(Utils::GetVisibleSize()) - Vec2(40, 40));
	pause->setScale(0.6f);
	addChild(pause);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (pause->getBoundingBox().containsPoint(location))
		{
			auto scene = PauseScene::createScene();
			Director::getInstance()->pushScene(scene);
			return true;
		}

		{
			auto nodeLocation = location - node->getPosition();
			Vec2 plMov = Utils::ResizeVec2(nodeLocation - player->getPosition(), Utils::bacteriaPushForce);
			float plArea = player->GetArea() * Utils::planktonAreaMul;
			PushCircleSprite(player, plMov, plArea);
			UpdateInfo();
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
		if ((*it)->Vulnerable(player) && CircleSprite::CenterDistance(*it, player) < (*it)->GetRadius() + player->GetRadius())
		{
			if (!CircleSprite::MassExchangeExplicit(*it, player, 5))
			{
				player->SetArea(player->GetArea() + (*it)->GetArea());
				AddScore((*it)->GetArea());

				planktons->removeChild(*it, true);
				planktons->list.erase(it);

				return;
			}
		}
		else
		{
			for (auto enemy : enemies->list)
			{
				if ((*it)->Vulnerable(enemy) && CircleSprite::CenterDistance(enemy, *it) < enemy->GetRadius() + (*it)->GetRadius())
				{
					if (!CircleSprite::MassExchangeExplicit(*it, enemy, 5))
					{
						enemy->SetArea(enemy->GetArea() + (*it)->GetArea());
						UpdateInfo();

						planktons->removeChild(*it, true);
						planktons->list.erase(it);

						return;
					}
				}
			}
		}
	}
}

void GameScene::EnemyPlayerCollision()
{
	for (auto it = enemies->list.begin(); it != enemies->list.end(); ++it)
	{
		if (CircleSprite::CenterDistance(player, *it) < player->GetRadius() + (*it)->GetRadius())
		{
			if (!CircleSprite::MassExchange(*it, player, Utils::minBacteriaRadius))
			{
				if (player->GetRadius() > (*it)->GetRadius())
				{
					if (enemies->list.size() == 1)
						GameOver("victory.png");

					player->SetArea(player->GetArea() + (*it)->GetArea());
					AddScore((*it)->GetArea());

					enemies->removeChild(*it, true);
					enemies->list.erase(it);

					return;
				}
				else
					GameOver("lose.png");
			}
		}
	}
}

void GameScene::update(float dt)
{
	Layer::update(dt);

	player->Tick(dt);
	planktons->Tick(dt);
	enemies->Tick(dt);

	EatPlankton();
	EnemyPlayerCollision();

	{
		Rect camRect(
			Vec2(player->getPosition().x - Utils::GetVisibleSize().width / 2, player->getPosition().y - Utils::GetVisibleSize().height / 2),
			Utils::GetVisibleSize()
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
	Utils::AddHighScore(score);
	auto scene = PauseScene::createScene(reason, false);
	Director::getInstance()->pushScene(scene);
}

void GameScene::AddScore(float score)
{
	this->score += score;
	UpdateInfo();
}

void GameScene::UpdateInfo()
{
	massText->setString("Mass: " + Utils::to_string(player->GetArea()) + "  Score: " + Utils::to_string(score));
}

bool GameScene::IsAlive(CircleSprite *sprite) const
{
	return (player == sprite) || std::any_of(enemies->list.begin(), enemies->list.end(), [sprite](Enemy *e){ return sprite == e; });
}

void GameScene::PushCircleSprite(CircleSprite *sprite, Vec2 const& velocity, float planktonArea)
{
	sprite->AddVelocity(velocity);
	sprite->SetArea(sprite->GetArea() - planktonArea);
	planktons->AddPlankton(sprite->getPosition(), planktonArea, sprite);
	planktons->list.back()->AddVelocity(velocity * Utils::planktonPushForceMul);
}
