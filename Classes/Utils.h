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
	static const float planktonAddScoreMul;
	static const float planktonDelScoreMul;
	static const float enemyAddScoreMul;
	static const float enemyDelScoreMul;

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
	static std::vector<float> GetHighScores();

	static cocos2d::Size GetVisibleSize();

	template <typename T>
	static T* CreateCocosObject(std::function<T*()> const& createFunc,
		std::function<bool(T*)> const& initFunc,
		std::function<void(T*)> const& afterInitFunc = [](T*){})
	{
		T *result = createFunc();

		if (result && initFunc(result))
		{
			result->autorelease();
			afterInitFunc(result);
			return result;
		}

		delete result;
		return nullptr;
	}

	template <typename T>
	static cocos2d::Scene* CreateScene(std::function<T*()> const& createFunc = [](){ return T::create(); })
	{
		cocos2d::Scene *scene = cocos2d::Scene::create();
		if (!scene)
			return nullptr;

		T *layer = createFunc();
		if (!layer)
			return nullptr;

		scene->addChild(layer);
		return scene;
	}
};
