#pragma once

#include "cocos2d.h"

class Enemy;
class GameScene;

class Enemies : public cocos2d::SpriteBatchNode
{
public:
	static Enemies* create(GameScene *gameScene);

	bool init(GameScene *gameScene);
	void Tick(float dt);
	void AddEnemy(cocos2d::Vec2 const& pos);

	std::list<Enemy*> list;

private:
	GameScene *gameScene;
};
