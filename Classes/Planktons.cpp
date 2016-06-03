#include "Planktons.h"
#include "Plankton.h"
#include "Utils.h"

USING_NS_CC;

Planktons* Planktons::create(GameScene *gameScene)
{
	Planktons *result = new (std::nothrow) Planktons();
	if (result && result->init(gameScene))
	{
		result->autorelease();
		return result;
	}
	CC_SAFE_DELETE(result);
	return nullptr;
}

bool Planktons::init(GameScene *gameScene)
{
	if (!SpriteBatchNode::initWithFile("Plankton.png"))
	{
		return false;
	}

	this->gameScene = gameScene;

	for (int i = 0; i < 250; ++i)
	{
		AddPlankton(Utils::RandVec2(), 500, nullptr);
	}

	return true;
}

void Planktons::Tick(float dt)
{
	for (auto p : list)
	{
		p->Tick(dt);
	}
}

void Planktons::AddPlankton(Vec2 pos, float area, CircleSprite *owner)
{
	auto p = Plankton::create(gameScene, getTexture(), owner);
	p->setPosition(pos);
	p->SetArea(area);
	list.push_back(p);
	addChild(p);
}
