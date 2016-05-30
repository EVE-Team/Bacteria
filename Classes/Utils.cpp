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

int Utils::Rand(int max)
{
	return rand() % max;
}

Vec2 Utils::RandVec2()
{
	return Vec2(Rand(fieldSize.width), Rand(fieldSize.height));
}

const Size Utils::fieldSize = Size(2000, 2000);
const float Utils::planktonAreaMul = 0.05;
const float Utils::bacteriaPushForceMul = 2000;
const float Utils::planktonPushForceMul = -0.1;

Utils::PolarVec2 Utils::LinearToPolar(Vec2 lin)
{
	PolarVec2 result;

	if (lin == Vec2())
	{
		result.angle = 0;
		result.dist = 0;
		return result;
	}

	result.dist = Utils::length(lin);

	if (lin.x == 0)
	{
		if (lin.y > 0)
			result.angle = M_PI / 2;
		else
			result.angle = -M_PI / 2;
	}
	else
	{
		result.angle = atan(lin.y / lin.x);
		if (lin.x < 0)
			result.angle += M_PI;
	}

	return result;
}

Vec2 Utils::PolarToLinear(PolarVec2 pol)
{
	return Vec2(pol.dist * cos(pol.angle), pol.dist * sin(pol.angle));
}

Vec2 Utils::ResizeVec2(Vec2 vec, float len)
{
	PolarVec2 pv = LinearToPolar(vec);
	pv.dist = len;
	return PolarToLinear(pv);
}
