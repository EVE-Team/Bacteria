#pragma once

#include "cocos2d.h"

class Utils
{
public:
	static float sqr(float a);
	static float length(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	static float length(cocos2d::Vec2 v);
	static int Rand(int max);
	static cocos2d::Vec2 RandVec2();

	static const cocos2d::Size fieldSize;
	static const float planktonAreaMul;
	static const float bacteriaPushForce;
	static const float planktonPushForceMul;
	static const float minBacteriaRadius;

	struct PolarVec2
	{
		float dist;
		float angle;
	};

	static PolarVec2 LinearToPolar(cocos2d::Vec2 lin);
	static cocos2d::Vec2 PolarToLinear(PolarVec2 pol);
	static cocos2d::Vec2 ResizeVec2(cocos2d::Vec2 vec, float len);

	template <typename T>
	static std::string to_string(T value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}

	static void AddHighScore(float score);
	static std::vector<float>& GetHighScores();

	static cocos2d::Size GetVisibleSize();
};
