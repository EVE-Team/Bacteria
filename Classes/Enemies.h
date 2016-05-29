#pragma once

#include "cocos2d.h"

class Enemy;

class Enemies : public cocos2d::SpriteBatchNode
{
public:
	static Enemies* create();

	bool init() override;
	void AddEnemy(cocos2d::Vec2 pos);

	std::list<Enemy*> list;
};
