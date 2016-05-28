#pragma once

#include "cocos2d.h"

class CircleSprite : public cocos2d::Sprite
{
public:
	float GetArea() const;
	void SetArea(float a);

protected:
	float picSize;

private:
	float GetRadius() const;
	void SetRadius(float r);
};
