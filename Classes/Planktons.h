#pragma once

#include "cocos2d.h"

class Plankton;

class Planktons : public cocos2d::SpriteBatchNode
{
public:
	static Planktons* create();

	bool init() override;
	void Tick(float dt);
	void AddPlankton(cocos2d::Vec2 pos);

	std::list<Plankton*> list;
};
