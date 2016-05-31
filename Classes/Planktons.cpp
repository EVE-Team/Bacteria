#include "Planktons.h"
#include "Plankton.h"
#include "Utils.h"

USING_NS_CC;

Planktons* Planktons::create()
{
	Planktons *result = new (std::nothrow) Planktons();
	if (result && result->init())
	{
		result->autorelease();
		return result;
	}
	CC_SAFE_DELETE(result);
	return nullptr;
}

bool Planktons::init()
{
	if (!SpriteBatchNode::initWithFile("Plankton.png"))
	{
		return false;
	}

	for (int i = 0; i < 250; ++i)
	{
		AddPlankton(Utils::RandVec2());
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

void Planktons::AddPlankton(Vec2 pos, float area)
{
	auto p = Plankton::create(getTexture(), area * 0.001);
	p->setPosition(pos);
	p->SetArea(area);
	list.push_back(p);
	addChild(p);
}
