#include "ButtonScene.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
#include "ShadowLabel.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ButtonScene::init(std::string const& backgroundPath)
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}


	auto background = Sprite::create(backgroundPath);
	background->setAnchorPoint(Vec2());
	addChild(background);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		for (auto button : buttons)
		{
			if (button.bgSprite->getBoundingBox().containsPoint(location))
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FX316.mp3");
				button.onClick();
				return true;
			}
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}

void ButtonScene::AddButton(std::string const& text, float posY, std::function<void()> const& onClick)
{
	Sprite *btnBg = Sprite::create("button.png");
	btnBg->setPosition(Vec2(Utils::GetVisibleSize().width / 2, posY));
	btnBg->setScaleX(1.2f);
	addChild(btnBg);

	ShadowLabel* label = ShadowLabel::createWithTTF(text, "fonts/Marker Felt.ttf", 36, Vec2(2, -2), Color3B(255, 255, 255), Color3B(0, 0, 0));
	label->setPosition(Vec2(Utils::GetVisibleSize().width / 2, posY));
	addChild(label);

	buttons.push_back(ClickableButton(label, btnBg, onClick));
}
