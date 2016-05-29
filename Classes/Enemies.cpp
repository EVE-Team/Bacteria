#include "Enemies.h"
#include "Enemy.h"
#include "Utils.h"

USING_NS_CC;

Enemies* Enemies::create()
{
	Enemies *result = new (std::nothrow) Enemies();
	if (result && result->init())
	{
		result->autorelease();
		return result;
	}
	CC_SAFE_DELETE(result);
	return nullptr;
}

bool Enemies::init()
{
	if (!SpriteBatchNode::initWithFile("Bacteria.png"))
	{
		return false;
	}

	for (int i = 0; i < 5; ++i)
	{
		AddEnemy(Utils::RandVec2());
	}

	return true;
}

void Enemies::AddEnemy(Vec2 pos)
{
	auto p = Enemy::create(getTexture());
	p->setPosition(pos);
	p->SetArea(5000);
	list.push_back(p);
	addChild(p);
}
