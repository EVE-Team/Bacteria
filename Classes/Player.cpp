#include "Player.h"
#include <math.h>

USING_NS_CC;

Player* Player::create()
{
	Player *sprite = new (std::nothrow) Player();
	if (sprite && sprite->initWithFile("Bacteria.png"))
	{
		sprite->autorelease();
		sprite->picSize = 1.0 * sprite->getContentSize().width / 2;
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
