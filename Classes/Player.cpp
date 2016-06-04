#include "Player.h"
#include "Utils.h"

USING_NS_CC;

Player* Player::create(cocos2d::Size const& fieldSize)
{
	return Utils::CreateCocosObject<Player>(
		[](){ return new (std::nothrow) Player(); },
		[](Player *s){ return s->initWithFile("Player.png"); },
		[&fieldSize](Player *s){ s->fieldSize = fieldSize; });
}
