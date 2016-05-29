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
	if (!SpriteBatchNode::initWithFile("Bacteria.png"))
	{
		return false;
	}

	for (int i = 0; i < 50; ++i)
	{
		AddPlankton(Utils::RandVec2());
	}

	return true;
}

void Planktons::AddPlankton(Vec2 pos)
{
	auto p = Plankton::create(getTexture());
	p->setPosition(pos);
	p->SetArea(1500);
	list.push_back(p);
	addChild(p);
}
