#pragma once

#include "CircleSprite.h"

class GameScene;

class Enemy : public CircleSprite
{
public:
	static Enemy* create(GameScene *gameScene, cocos2d::Texture2D *texture);
	void Tick(float dt) override;

	GameScene *gameScene;
};
