#include "Enemies.h"
#include "Enemy.h"
#include "Utils.h"
#include "GameScene.h"
#include "Player.h"

USING_NS_CC;

Enemies* Enemies::create(GameScene *gameScene)
{
	return Utils::CreateCocosObject<Enemies>(
		[](){ return new (std::nothrow) Enemies(); },
		[gameScene](Enemies *s){ return s->init(gameScene); });
}

bool Enemies::init(GameScene *gameScene)
{
	if (!SpriteBatchNode::initWithFile("Enemy.png"))
	{
		return false;
	}

	this->gameScene = gameScene;

	for (int i = 0; i < gameScene->GetGameData().enemyCount; ++i)
	{
		AddEnemy(Utils::RandVec2WithFilter(gameScene->GetGameData().fieldSize, gameScene->player->getPosition(), 400));
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

void Enemies::AddEnemy(Vec2 const& pos)
{
	auto p = Enemy::create(gameScene, getTexture());
	p->setPosition(pos);
	p->SetArea(5000);
	list.push_back(p);
	addChild(p);
}

void Enemies::DeleteEnemy(std::list<Enemy*>::iterator const& it)
{
	removeChild(*it, true);
	list.erase(it);
}
