#include "Enemy.h"

USING_NS_CC;

Enemy* Enemy::create(Texture2D *texture)
{
	Enemy *sprite = new (std::nothrow) Enemy();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		sprite->picSize = 1.0 * sprite->getContentSize().width / 2;
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
