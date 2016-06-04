#include "MenuScene.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return Utils::CreateScene<MenuScene>();
}

MenuScene* MenuScene::create()
{
	return Utils::CreateCocosObject<MenuScene>(
		[](){ return new (std::nothrow) MenuScene(); },
		[](MenuScene *s){ return s->init(); });
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2());
	addChild(background);

	{
		auto label = Sprite::create("title.png");
		label->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 400));
		addChild(label);
	}


	AddButton("New game", 300, [](){
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Scores", 200, [](){
		auto scene = ScoreScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Exit", 100, [](){
		Director::getInstance()->end();
	});


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		for (auto button : buttons)
		{
			if (button.bgSprite->getBoundingBox().containsPoint(location))
			{
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

void MenuScene::AddButton(std::string const& text, float posY, std::function<void()> const& onClick)
{
	Sprite *btnBg = Sprite::create("button.png");
	btnBg->setPosition(Vec2(Utils::GetVisibleSize().width / 2, posY));
	btnBg->setScaleX(1.2f);
	addChild(btnBg);

	Label* label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 36);
	label->setPosition(Vec2(Utils::GetVisibleSize().width / 2, posY));
	addChild(label);

	buttons.push_back(ClickableButton(label, btnBg, onClick));
}
