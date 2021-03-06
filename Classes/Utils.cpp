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

Vec2 Utils::RandVec2(Size const& fieldSize)
{
	return Vec2(Rand(fieldSize.width), Rand(fieldSize.height));
}

Vec2 Utils::RandVec2WithFilter(Size const& fieldSize, Vec2 const& playerPos, float minDist)
{
	for (;;)
	{
		auto v = RandVec2(fieldSize);
		if (length(v - playerPos) > minDist)
			return v;
	}
}

const float Utils::planktonAreaMul = 0.05f;
const float Utils::bacteriaPushForce = 200;
const float Utils::planktonPushForceMul = -1;
const float Utils::minBacteriaRadius = 25;
const float Utils::planktonAddScoreMul = 0.25f;
const float Utils::planktonDelScoreMul = 0.3f;
const float Utils::enemyAddScoreMul = 1;
const float Utils::enemyDelScoreMul = 1.25f;
const float Utils::planktonEatVolume = 0.25f;

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
			result.angle = (float)M_PI / 2;
		else
			result.angle = -(float)M_PI / 2;
	}
	else
	{
		result.angle = atan(lin.y / lin.x);
		if (lin.x < 0)
			result.angle += (float)M_PI;
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

static std::vector<float> ReadHighScores()
{
	std::vector<float> result;
	result.resize(UserDefault::getInstance()->getIntegerForKey("hsCount", 0));

	for (size_t i = 0; i < result.size(); ++i)
	{
		result[i] = UserDefault::getInstance()->getFloatForKey(("hsValue" + Utils::to_string(i)).c_str());
	}
	return result;
}

static void SaveHighScores(std::vector<float> const& highScores)
{
	UserDefault::getInstance()->setIntegerForKey("hsCount", highScores.size());

	for (size_t i = 0; i < highScores.size(); ++i)
	{
		UserDefault::getInstance()->setFloatForKey(("hsValue" + Utils::to_string(i)).c_str(), highScores[i]);
	}
}

void Utils::AddHighScore(float score)
{
	auto highScores = ReadHighScores();

	highScores.push_back(score);
	std::sort(highScores.begin(), highScores.end(), [](float a, float b){ return a > b; });
	if (highScores.size() > 5)
	{
		highScores.pop_back();
	}

	SaveHighScores(highScores);
}

std::vector<float> Utils::GetHighScores()
{
	return ReadHighScores();
}

Size Utils::GetVisibleSize()
{
	return Director::getInstance()->getVisibleSize();
}
