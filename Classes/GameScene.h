#pragma once

#include "cocos2d.h"

class Player;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	cocos2d::Sprite *pause;
	Player *player;
};
