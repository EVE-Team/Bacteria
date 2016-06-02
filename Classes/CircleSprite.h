#pragma once

#include "cocos2d.h"

class CircleSprite : public cocos2d::Sprite
{
public:
	static float CenterDistance(CircleSprite *a, CircleSprite *b);
	static bool MassExchange(CircleSprite *a, CircleSprite *b);

	float GetRadius() const;
	void SetRadius(float r);
	float GetArea() const;
	void SetArea(float a);
	void AddVelocity(cocos2d::Vec2 vel);
	virtual void Tick(float dt);
	cocos2d::Vec2 GetVelocity() const;

protected:
	float picSize;

private:
	cocos2d::Vec2 vel;
};
