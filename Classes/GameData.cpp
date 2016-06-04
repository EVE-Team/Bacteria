#include "GameData.h"

USING_NS_CC;

const int GameData::levelCount = 3;

GameData GameData::GetLevelData(int level)
{
	GameData result;
	assert(level > 0 && level <= levelCount);

	switch (level)
	{
	case 1:
		result.enemyCount = 8;
		result.planktonCount = 50;
		result.fieldSize = Size(1200, 1200);
		break;

	case 2:
		result.enemyCount = 15;
		result.planktonCount = 100;
		result.fieldSize = Size(2000, 2000);
		break;

	case 3:
		result.enemyCount = 30;
		result.planktonCount = 250;
		result.fieldSize = Size(3000, 3000);
		break;
	}

	return result;
}
