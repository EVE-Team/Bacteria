#pragma once

#include "cocos2d.h"

class CircleSprite : public cocos2d::Sprite
{
public:
	static bool Collide(CircleSprite *a, CircleSprite *b);

	float GetRadius() const;
	void SetRadius(float r);
	float GetArea() const;
	void SetArea(float a);
	void SetVel(cocos2d::Vec2 vel);
	virtual void Tick(float dt);

protected:
	float picSize;

private:
	cocos2d::Vec2 vel;
};
