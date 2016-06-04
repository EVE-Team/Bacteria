#pragma once

#include "cocos2d.h"

class GameData
{
public:
	static const int levelCount;
	static GameData GetLevelData(int level);

	int enemyCount;
	int planktonCount;
	cocos2d::Size fieldSize;
};
