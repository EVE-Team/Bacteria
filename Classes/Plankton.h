#pragma once

#include "CircleSprite.h"

class GameScene;

class Plankton : public CircleSprite
{
public:
	static Plankton* create(GameScene *gameScene, cocos2d::Texture2D *texture, CircleSprite *owner);

	Plankton(GameScene *gameScene, CircleSprite *owner);
	void Tick(float dt) override;
	bool Vulnerable(CircleSprite *attacker) const;

private:
	GameScene *gameScene;
	CircleSprite *owner;
};
