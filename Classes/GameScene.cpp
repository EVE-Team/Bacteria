#include "GameScene.h"
#include "PauseScene.h"
#include "Player.h"
#include "Planktons.h"
#include "Utils.h"
#include "Plankton.h"
#include "Enemies.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "WinScene.h"
#include "LoseScene.h"
#include "EndScene.h"
#include "ShadowLabel.h"

USING_NS_CC;

Scene* GameScene::createScene(GameProgress const& progress)
{
	return Utils::CreateScene<GameScene>([&progress](){ return GameScene::create(progress); });
}

GameScene* GameScene::create(GameProgress const& progress)
{
	return Utils::CreateCocosObject<GameScene>(
		[](){ return new (std::nothrow) GameScene(); },
		[&progress](GameScene *s){ return s->init(progress); });
}

bool GameScene::init(GameProgress const& progress)
{
	if ( !Layer::init() )
		return false;


	score = progress.score;
	startProgress = progress;
	gameData = GameData::GetLevelData(progress.level);


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
	background->setTextureRect(Rect(Vec2(), gameData.fieldSize));
	background->setAnchorPoint(Vec2());
	node->addChild(background);

	player = Player::create(gameData.fieldSize);
	player->SetArea(5000);
	player->setPosition(Vec2(gameData.fieldSize) / 2);

	planktons = Planktons::create(this);
	enemies = Enemies::create(this);

	node->addChild(planktons);
	node->addChild(enemies);
	node->addChild(player);

	massText = ShadowLabel::createWithTTF("", "fonts/Marker Felt.ttf", 24, Vec2(2, -2), Color3B(255, 255, 255), Color3B(0, 0, 0));
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
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX316.mp3");
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
	for (auto it = planktons->list.begin(); it != planktons->list.end();)
	{
		if ((*it)->Vulnerable(player) && CircleSprite::CenterDistance(*it, player) < (*it)->GetRadius() + player->GetRadius())
		{
			float oldArea = (*it)->GetArea();

			if (!CircleSprite::MassExchangeExplicit(*it, player, 5))
			{
				player->SetArea(player->GetArea() + (*it)->GetArea());
				AddScore((*it)->GetArea() * Utils::planktonAddScoreMul);

				planktons->DeletePlankton(it++);

				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX318.mp3", false, 1.0f, 0.0f, Utils::planktonEatVolume);
			}
			else
			{
				float gotArea = oldArea - (*it)->GetArea();
				AddScore(gotArea * Utils::planktonAddScoreMul);
				++it;
			}
		}
		else
		{
			bool planktonKilled = false;

			for (auto enemy : enemies->list)
			{
				if (planktonKilled)
					break;

				if ((*it)->Vulnerable(enemy) && CircleSprite::CenterDistance(enemy, *it) < enemy->GetRadius() + (*it)->GetRadius())
				{
					if (!CircleSprite::MassExchangeExplicit(*it, enemy, 5))
					{
						enemy->SetArea(enemy->GetArea() + (*it)->GetArea());
						UpdateInfo();

						planktons->DeletePlankton(it++);
						planktonKilled = true;
					}
				}
			}

			if (!planktonKilled)
				++it;
		}
	}
}

void GameScene::EnemyPlayerCollision()
{
	for (auto it = enemies->list.begin(); it != enemies->list.end();)
	{
		bool enemyKilled = false;

		if (CircleSprite::CenterDistance(player, *it) < player->GetRadius() + (*it)->GetRadius())
		{
			float oldArea = (*it)->GetArea();

			if (!CircleSprite::MassExchange(*it, player, Utils::minBacteriaRadius))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX312.mp3");

				if (player->GetRadius() > (*it)->GetRadius())
				{
					if (enemies->list.size() == 1)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX320.mp3");

						if (startProgress.level < GameData::levelCount)
						{
							auto scene = WinScene::createScene(startProgress, score);
							Director::getInstance()->replaceScene(scene);
						}
						else
						{
							Utils::AddHighScore(score);
							auto scene = EndScene::createScene();
							Director::getInstance()->replaceScene(scene);
						}
					}

					player->SetArea(player->GetArea() + (*it)->GetArea());
					AddScore((*it)->GetArea() * Utils::enemyAddScoreMul);

					enemies->DeleteEnemy(it++);
					enemyKilled = true;
				}
				else
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GAMEOVER.ogg");
					DelScore(player->GetArea() * Utils::enemyDelScoreMul);

					auto scene = LoseScene::createScene(startProgress);
					Director::getInstance()->replaceScene(scene);
				}
			}
			else
			{
				if (oldArea > (*it)->GetArea())
				{
					float gotArea = oldArea - (*it)->GetArea();
					AddScore(gotArea * Utils::enemyAddScoreMul);
				}
				else if (oldArea < (*it)->GetArea())
				{
					float lostArea = (*it)->GetArea() - oldArea;
					DelScore(lostArea * Utils::enemyDelScoreMul);
				}
			}
		}

		if (!enemyKilled)
			++it;
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
		else if (camRect.getMaxX() > gameData.fieldSize.width)
			camRect.origin.x -= (camRect.getMaxX() - gameData.fieldSize.width);

		if (camRect.getMinY() < 0)
			camRect.origin.y = 0;
		else if (camRect.getMaxY() > gameData.fieldSize.height)
			camRect.origin.y -= (camRect.getMaxY() - gameData.fieldSize.height);

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

void GameScene::AddScore(float score)
{
	assert(score > 0);
	this->score += score;
	UpdateInfo();
}

void GameScene::DelScore(float score)
{
	assert(score > 0);
	this->score -= score;
	if (this->score < 0)
		this->score = 0;
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
	planktons->AddPlanktonWithVel(sprite->getPosition(), planktonArea, sprite, velocity * Utils::planktonPushForceMul);

	if (sprite == player)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX318.mp3", false, 1.0f, 0.0f, Utils::planktonEatVolume);
		DelScore(planktonArea * Utils::planktonDelScoreMul);
	}
}

const GameData& GameScene::GetGameData() const
{
	return gameData;
}
