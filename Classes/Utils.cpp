#include "Utils.h"

USING_NS_CC;

float Utils::sqr(float a)
{
	return a * a;
}

float Utils::length(Vec2 p1, Vec2 p2)
{
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

float Utils::length(Vec2 v)
{
	return length(Vec2(), v);
}
