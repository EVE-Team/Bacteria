#pragma once

#include "cocos2d.h"

class Plankton;

class Planktons : public cocos2d::SpriteBatchNode
{
public:
	static Planktons* create();

	bool init() override;

private:
	std::vector<Plankton*> list;

	void AddPlankton(cocos2d::Vec2 pos);
};
