#include "Enemies.h"
#include "Enemy.h"
#include "Utils.h"

USING_NS_CC;

Enemies* Enemies::create(GameScene *gameScene)
{
	Enemies *result = new (std::nothrow) Enemies();
	if (result && result->init(gameScene))
	{
		result->autorelease();
		return result;
	}
	CC_SAFE_DELETE(result);
	return nullptr;
}

bool Enemies::init(GameScene *gameScene)
{
	if (!SpriteBatchNode::initWithFile("Enemy.png"))
	{
		return false;
	}

	this->gameScene = gameScene;

	for (int i = 0; i < 15; ++i)
	{
		AddEnemy(Utils::RandVec2());
	}

	return true;
}

void Enemies::Tick(float dt)
{
	for (auto enemy : list)
	{
		enemy->Tick(dt);
	}
}

void Enemies::AddEnemy(Vec2 pos)
{
	auto p = Enemy::create(gameScene, getTexture());
	p->setPosition(pos);
	p->SetArea(7500);
	list.push_back(p);
	addChild(p);
}
