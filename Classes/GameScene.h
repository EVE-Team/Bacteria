#pragma once

#include "cocos2d.h"

class Player;
class Planktons;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	virtual void update(float dt) override;
	virtual void onEnter() override;
	virtual void onExit() override;

private:
	cocos2d::Sprite *pause;
	Player *player;
	Planktons *planktons;
};
