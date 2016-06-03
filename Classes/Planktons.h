#pragma once

#include "cocos2d.h"

class Plankton;
class CircleSprite;
class GameScene;

class Planktons : public cocos2d::SpriteBatchNode
{
public:
	static Planktons* create(GameScene *gameScene);

	bool init(GameScene *gameScene);
	void Tick(float dt);
	void AddPlankton(cocos2d::Vec2 pos, float area, CircleSprite *owner);

	std::list<Plankton*> list;

private:
	GameScene *gameScene;
};
