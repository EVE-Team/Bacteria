#include "Planktons.h"
#include "Plankton.h"
#include "Utils.h"
#include "GameScene.h"

USING_NS_CC;

Planktons* Planktons::create(GameScene *gameScene)
{
	return Utils::CreateCocosObject<Planktons>(
		[](){ return new (std::nothrow) Planktons(); },
		[gameScene](Planktons *s){ return s->init(gameScene); });
}

bool Planktons::init(GameScene *gameScene)
{
	if (!SpriteBatchNode::initWithFile("Plankton.png"))
	{
		return false;
	}

	this->gameScene = gameScene;

	for (int i = 0; i < gameScene->GetGameData().planktonCount; ++i)
	{
		AddPlankton(Utils::RandVec2(gameScene->GetGameData().fieldSize), 1000, nullptr);
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

void Planktons::AddPlanktonWithVel(cocos2d::Vec2 pos, float area, CircleSprite *owner, cocos2d::Vec2 const& vel)
{
	AddPlankton(pos, area, owner);
	list.back()->AddVelocity(vel);
}

void Planktons::DeletePlankton(std::list<Plankton*>::iterator const& it)
{
	removeChild(*it, true);
	list.erase(it);
}
