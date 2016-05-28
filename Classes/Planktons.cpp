#include "Planktons.h"
#include "Plankton.h"

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

	AddPlankton(Vec2(200, 200));
	AddPlankton(Vec2(300, 200));
	AddPlankton(Vec2(400, 200));
	AddPlankton(Vec2(500, 200));

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
