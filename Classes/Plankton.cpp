#include "Plankton.h"

USING_NS_CC;

Plankton* Plankton::create(Texture2D *texture)
{
	Plankton *sprite = new (std::nothrow) Plankton();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		sprite->picSize = 1.0 * sprite->getContentSize().width / 2;
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
